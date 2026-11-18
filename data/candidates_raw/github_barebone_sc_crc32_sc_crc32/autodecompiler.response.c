__attribute__((used)) static u32 crc32_le(u32 crc, unsigned char const *p, size_t len)
{
	return crc32_sw_le(crc, p, len);
}