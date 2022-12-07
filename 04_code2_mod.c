#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "06_s_modul.c"
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
    signal(Id_Semaforo, 0);
    sleep(1);
    //printf("Levanto Semaforo 2\n");
    //signal(Id_Semaforo, 1);
    //sleep(1);
  }
}
