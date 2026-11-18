int __cdecl write_data(int fd, const unsigned __int8 *buf, int size)
{
  int bytes_written; // Replaces 'ret'. Tracks the number of bytes written in the latest write() call.
  int total_written; // Replaces 'cur'. Tracks the total number of bytes written so far.

  // Loop until the exact requested number of bytes has been written
  for ( total_written = 0; total_written != size; total_written += bytes_written )
  {
    // Attempt to write the remaining bytes. 
    // Note: If size is 0, the loop is bypassed and it returns 0 immediately.
    bytes_written = write(fd, &buf[total_written], size - total_written);
    
    // write() returns the number of bytes written, or 0/-1 on failure/EOF.
    // If no bytes were written or an error occurred, abort and return -1.
    if ( bytes_written <= 0 )
      return -1;
  }
  
  return 0;
}