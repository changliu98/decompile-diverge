void cgi_sys_get_action(char *shm)
{
    *(shm+4) = 6;
    *(shm+5) = 0;
    *(shm+6) = 0;
    *(shm+7) = 0;
    *(shm+8) = 1;
    *(shm+9) = 0;
    *(shm+10) = 0;
    *(shm+11) = 0;
}