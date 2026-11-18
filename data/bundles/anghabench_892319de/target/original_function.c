char *dlfb_dummy_render(char *buf)
{
	*buf++ = 0xAF;
	*buf++ = 0x6A; /* copy */
	*buf++ = 0x00; /* from address*/
	*buf++ = 0x00;
	*buf++ = 0x00;
	*buf++ = 0x01; /* one pixel */
	*buf++ = 0x00; /* to address */
	*buf++ = 0x00;
	*buf++ = 0x00;
	return buf;
}