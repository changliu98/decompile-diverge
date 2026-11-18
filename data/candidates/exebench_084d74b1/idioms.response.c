int MPI_Comm_create(int comm, int *newcomm)
{
  *newcomm = comm;
  return(MPI_SUCCESS);
}