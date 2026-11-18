void __cdecl cgi_network_get_action(char *shm)
{
  *((_DWORD *)shm + 1) = 2;
  *((_DWORD *)shm + 2) = 1;
}