int write_bus(int fd, char *buf, int len)
{
	return read(fd, buf, len);
}