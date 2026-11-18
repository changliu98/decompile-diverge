int readBytes(int busHandle, int addr, unsigned char *buf, int len)
{
    if (ioctl(busHandle, 0x703, addr) >= 0) {
        return read(busHandle, buf, len);
    }
    
    return -1;
}