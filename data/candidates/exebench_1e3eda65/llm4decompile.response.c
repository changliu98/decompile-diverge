int Serial_WriteData(int fd, unsigned char *pData, int size)
{
 int nWritten = 0;

 nWritten = write(fd, pData, size);

 return nWritten;
}