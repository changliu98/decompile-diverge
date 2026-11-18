int Serial_WriteData(int fd, char *buf, int len)
{
	return read(fd, buf, len);
}