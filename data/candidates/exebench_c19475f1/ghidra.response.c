void cgi_store_get_action(char *shm)

{
  char *shm_local;
  
  shm[4] = '\x04';
  shm[5] = '\0';
  shm[6] = '\0';
  shm[7] = '\0';
  shm[8] = '\x01';
  shm[9] = '\0';
  shm[10] = '\0';
  shm[0xb] = '\0';
  return;
}