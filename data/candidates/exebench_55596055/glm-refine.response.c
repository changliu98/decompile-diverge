void clean_fd(int sock, int *cache_sock, int *nsock)
{
  // Clear the socket from the cache if it exists in the first two slots
  for (int i = 0; i < 2; ++i)
  {
    if (cache_sock[i] == sock)
      cache_sock[i] = 0;
  }

  // Close the file descriptor and decrement the active socket count
  close(sock);
  (*nsock)--;
}