void shmDetach(const void *shmaddr)
{
 shmdt(shmaddr);
}