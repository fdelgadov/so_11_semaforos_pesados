#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
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
  int i = 0;
  Clave = ftok("/bin/ls", 33);
  if (Clave == (key_t) -1) {
    printf("No puedo conseguir clave de semaforo \n");
    exit(0);
  }
  Id_Semaforo = semget(Clave, 10, 0600 | IPC_CREAT);
  if (Id_Semaforo == -1) {
    printf("No puedo crear semaforo \n");
    exit(0);
  }
  
  while (1) {
    printf(" Esperando Semaforo %d \n", i);
    wait(Id_Semaforo, 0);
    printf(" Salgo del Semaforo %d \n", i);
    i++;
  }
}
