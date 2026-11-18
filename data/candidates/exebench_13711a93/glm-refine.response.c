void __cdecl cgi_sys_get_action(char *shm)
{
  int *shm_int = (int *)shm;
  shm_int[1] = 6;
  shm_int[2] = 1;
}