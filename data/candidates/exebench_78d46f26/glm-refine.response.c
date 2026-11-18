void __cdecl get_proc_info_mpi(int *myid, int *nprocs)
{
  if (myid && nprocs) {
    *myid = 0;   // Default rank is 0
    *nprocs = 1; // Default number of processes is 1
  }
}