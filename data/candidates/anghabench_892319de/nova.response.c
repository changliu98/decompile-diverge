static unsigned char *dlfb_dummy_render(unsigned char *payload)
{
	*payload++ = 0xaf;
	*payload++ = 0x6a;
	*payload++ = 0x00;
	*payload++ = 0x00;
	*payload++ = 0x00;
	*payload++ = 0x01;
	*payload++ = 0x00;
	*payload++ = 0x00;

	return payload;
}