int MPI_Allreduce(void *sendbuf, void *recvbuf, int count, int datatype, int op, int comm)
{
  int *intbuf = (int *)sendbuf;
  int *intbuf2 = (int *)recvbuf;
  intbuf2[0] = 0;
  intbuf[0] = 0;
  return 0;
}