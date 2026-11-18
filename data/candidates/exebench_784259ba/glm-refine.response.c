int __cdecl inet_close(int *sk)
{
  // Close the socket file descriptor
  close(*sk);
  
  // Reset the socket descriptor to 0 to prevent dangling references 
  // and accidental reuse (e.g., double-close)
  *sk = 0;
  
  return 0;
}