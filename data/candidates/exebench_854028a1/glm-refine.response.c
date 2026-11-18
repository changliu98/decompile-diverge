void __cdecl closep(int *fd)
{
  // Check if the file descriptor is valid (0 or positive)
  if ( *fd >= 0 )
  {
    // Close the file descriptor
    close(*fd);
  }
  
  // Invalidate the file descriptor pointer
  *fd = -1;
}