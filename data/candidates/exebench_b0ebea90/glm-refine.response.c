define CW_LEN 0x12

int __cdecl sendcw(int fd, unsigned char *buff) 
{
    if (send(fd, buff, CW_LEN, 0) != -1) {
        return 1;
    }

    int err = *__errno_location();
    syslog(LOG_ERR, "ca.so: Send cw failed %d", err);
    
    return 0;
}