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

void wait(int s){
  struct sembuf op;
  op.sem_num = s;
  op.sem_op = -1;
  op.sem_flg = 0;
  semop(Id_Semaforo, &op, 1);
}
int main() {
  key_t Clave;
  struct sembuf Operacion;
  union semun arg;
  int i = 0;
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

  while(1) {
    printf(" Esperando Semaforo %d \n", i);
    wait(1);
    printf(" Salgo del Semaforo %d \n", i);
    i++;
  }
}
