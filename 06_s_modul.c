void wait(int Id_Semaforo, int s){
  struct sembuf op;
  op.sem_num = s;
  op.sem_op = -1;
  op.sem_flg = 0;
  semop(Id_Semaforo, &op, 1);
}
void signal(int Id_Semaforo, int s){
  struct sembuf op;
  op.sem_num = s;
  op.sem_op = 1;
  op.sem_flg = 0;
  semop(Id_Semaforo, &op, 1);
}