short recv_data(WEATHERSTATION serdevice, unsigned char *buffer, unsigned short buffer_size)
{







 int ret = read(serdevice, buffer, buffer_size);







 return ret;
}