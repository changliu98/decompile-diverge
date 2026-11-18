int MPI_Comm_create(MPI_Comm comm, MPI_Comm *comm_out)
{
  *comm_out = comm;
  return 0;
}