void __cdecl clib_mcheck(int *ierr)
{
  // Dereference the output pointer and set the status to 2
  if (ierr) 
  {
    *ierr = 2; 
  }
}