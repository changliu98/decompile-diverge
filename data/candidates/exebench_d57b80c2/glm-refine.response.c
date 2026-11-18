int __cdecl i2c_multiple_writes(int fd, int num, unsigned __int8 *Ptr_buff)
{
  int bytes_written; 

  bytes_written = write(fd, Ptr_buff, (size_t)num);
  
  // Check if the write operation was successful and all bytes were written
  if (bytes_written != -1 && bytes_written == num)
    return bytes_written;
  else
    return -1;
}