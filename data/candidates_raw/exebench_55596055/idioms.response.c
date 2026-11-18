void close_socket(int socket, int cache_socket[], int *nsock)
{
  int i;
  for (i = 0; i < 2; i++)
  {
    if (cache_socket[i] == socket)
    {
      cache_socket[i] = 0;
    }
  }
  close(socket);
  (*nsock)--;
}