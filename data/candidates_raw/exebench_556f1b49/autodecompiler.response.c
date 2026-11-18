int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *comm_out)
{
  if (color > 0)
  {
    *comm_out = 0;
  }
  else
  {
    *comm_out = comm;
  }

  return 0;
}