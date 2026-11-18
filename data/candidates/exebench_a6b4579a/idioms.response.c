int lockoff(struct sem_t *sem, int pshared, unsigned int value)
{
  sem->sem_num = 0;
  return 0;
}