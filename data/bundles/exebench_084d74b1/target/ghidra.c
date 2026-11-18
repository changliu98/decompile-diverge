int MPI_Comm_create(int comm,int group,int *newcomm)

{
  int *newcomm_local;
  int group_local;
  int comm_local;
  
  *newcomm = group;
  return 0;
}