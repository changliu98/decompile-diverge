void cgi_store_get_action(char *shm)
{
    *shm = 4;
    *(shm+1) = 0;
    *(shm+2) = 0;
    *(shm+3) = 0;
    *(shm+4) = 1;
    *(shm+5) = 0;
    *(shm+6) = 0;
    *(shm+7) = 0;
}