static int bitsToIp4AddrArr(u32 cpu_id, u8 *result)
{
	result[0] = (cpu_id & 0xff000000) >> 24;
	result[1] = (cpu_id & 0x00ff0000) >> 16;
	result[2] = (cpu_id & 0x0000ff00) >> 8;
	result[3] = (cpu_id & 0x000000ff);

	return 0;
}