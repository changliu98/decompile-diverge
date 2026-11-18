static void edosk2674_smsc_outw(unsigned short data, unsigned char *buf)
{
	buf[0] = data >> 8;
	buf[1] = data << 8;
}