void __cdecl cgi_sys_get_action(char *shm)
{
  *((_DWORD *)shm + 1) = 6;
  *((_DWORD *)shm + 2) = 1;
}