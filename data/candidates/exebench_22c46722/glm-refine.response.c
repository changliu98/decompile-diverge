int __cdecl read_sock(int sockhandle, unsigned __int8 *buf, int length)
{
  int bytes_read;

  // Limit the number of read attempts to prevent infinite blocking
  for (int attempts = 0; attempts <= 10000; attempts++)
  {
    // If we have read the requested amount of data, exit the loop
    if (length <= 0)
      break;

    bytes_read = read(sockhandle, buf, (unsigned int)length);
    
    if (bytes_read > 0)
    {
      // Advance the buffer pointer and decrease the remaining length
      buf += bytes_read;
      length -= bytes_read;
    }
  }

  // If the loop exceeded 10000 attempts, return an error (-1)
  // Otherwise, return the remaining length (which will be 0 on full success)
  if (length > 0)
    return -1;
    
  return length;
}