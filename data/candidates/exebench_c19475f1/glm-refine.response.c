void __cdecl cgi_store_get_action(char *shm)
{
  // Assuming 32-bit integers (as implied by _DWORD)
  int *shm_int = (int *)shm;
  
  shm_int[1] = 4; // Offset +4 bytes
  shm_int[2] = 1; // Offset +8 bytes
}