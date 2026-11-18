void __cdecl cgi_alert_get_action(char *shm)
{
  *((_DWORD *)shm + 1) = 3;
  *((_DWORD *)shm + 2) = 1;
}