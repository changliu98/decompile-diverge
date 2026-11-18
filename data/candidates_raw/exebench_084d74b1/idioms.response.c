int MPI_Comm_dup(int comm, int *newcomm)
{
  *newcomm = comm;
  return(MPI_SUCCESS);
}