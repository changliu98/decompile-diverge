int MPI_Comm_group(int comm, int n, int *ranks, int *newgroup)
{
  if (n > 0)
    *newgroup = 0;
  else
    *newgroup = comm;
  return (MPI_SUCCESS);
}