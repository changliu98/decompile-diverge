void __cdecl clean_fd(int sock, int *cache_sock, int *nsock)
{
  int i; // [rsp+4h] [rbp-1Ch]

  for ( i = 0; i < 2; ++i )
  {
    if ( cache_sock[i] == sock )
      cache_sock[i] = 0;
  }
  close(sock);
  --*nsock;
}