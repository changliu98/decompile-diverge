void __cdecl cgi_store_get_action(char *shm)
{
  *((_DWORD *)shm + 1) = 4;
  *((_DWORD *)shm + 2) = 1;
}