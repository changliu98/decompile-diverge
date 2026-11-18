int __cdecl MPI_Cart_shift(int comm, int direction, int displ, int *source, int *dest)
{
  // Unused parameters in this stubbed implementation
  (void)comm;
  (void)direction;
  (void)displ;

  // Safely initialize output parameters to 0 (MPI_PROC_NULL is typically -1, 
  // but this stub uses 0 as a default null/empty state)
  if (source) {
    *source = 0;
  }
  
  if (dest) {
    *dest = 0;
  }

  return 0; // MPI_SUCCESS
}