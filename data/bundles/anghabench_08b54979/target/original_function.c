uint32_t F(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | ((~x) & z);
}