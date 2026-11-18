void __cdecl cgi_network_get_action(char *shm)
{
  // Cast the base pointer to a DWORD (32-bit integer) pointer 
  // to calculate offsets in terms of 4-byte elements rather than bytes.
  _DWORD *shm_dword = (_DWORD *)shm;
  
  // Offset 1 corresponds to byte offset 0x04
  shm_dword[1] = 2; 
  
  // Offset 2 corresponds to byte offset 0x08
  shm_dword[2] = 1; 
}