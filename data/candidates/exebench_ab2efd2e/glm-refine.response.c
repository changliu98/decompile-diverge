void __cdecl cgi_alert_get_action(char *shm)
{
  // Cast the shared memory pointer to a 32-bit integer pointer 
  // to make the offset calculations much clearer.
  _DWORD *shm_dword = (_DWORD *)shm;
  
  // Offset 1 corresponds to byte offset 0x04
  shm_dword[1] = 3; 
  
  // Offset 2 corresponds to byte offset 0x08
  shm_dword[2] = 1; 
}