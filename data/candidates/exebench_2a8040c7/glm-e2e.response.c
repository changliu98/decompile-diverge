void shmDetach(void *shmaddr) {
    shmdt(shmaddr);
}