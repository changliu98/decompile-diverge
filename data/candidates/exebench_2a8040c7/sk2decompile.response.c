int shmDetach(void *shmaddr) {
  int ret;
  ret = shmdt(shmaddr);
  return ret;
}