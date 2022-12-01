#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
#else
union semun {
  int val;
  struct semid_ds* buf;
  unsigned short int* array;
  struct seminfo* __buf;
};
#endif
int Id_Semaforo;

void signal(int s){
  struct sembuf op;
  op.sem_num = s;
  op.sem_op = 1;
  op.sem_flg = 0;
  semop(Id_Semaforo, &op, 1);
}
int main() {
  key_t Clave;
  union semun arg;
  int i;
  Clave = ftok("/bin/ls", 33);
  if (Clave == (key_t) -1) {
    printf("No puedo conseguir clave de semaforo \n ");
    exit(0);
  }
  Id_Semaforo = semget(Clave, 10, 0600 | IPC_CREAT);
  if (Id_Semaforo == -1) {
    printf("No puedo crear semaforo \n");
    exit(0);
  }

  for (i = 0; i < 10; i++) {
    printf("Levanto Semaforo 1\n");
    signal(0);
    sleep(1);
    printf("Levanto Semaforo 2\n");
    signal(1);
    sleep(1);
  }
}
