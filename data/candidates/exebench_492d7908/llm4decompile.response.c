void edosk2674_smsc_outw(unsigned short value, unsigned long port)
{
	*(volatile unsigned short *)port = (value << 8) | (value >> 8);
}