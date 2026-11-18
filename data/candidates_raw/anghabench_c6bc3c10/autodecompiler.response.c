static int map_16k_to_32k(int addr)
{
 return 0xe28a + (addr << 0);
}