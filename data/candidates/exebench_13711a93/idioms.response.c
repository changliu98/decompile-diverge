void cgi_sys_get_action(struct shm *shm)
{
  shm->is_init = 1;
  shm->is_lock = 1;
  return ;
}