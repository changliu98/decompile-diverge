uint32_t sc_crc32(uint32_t crc, const void *buf, size_t len)
{
#ifdef HAVE_CRC32C
	return crc32_hw(crc, buf, len);
#else
#ifdef HAVE_BIG_ENDIAN
	return crc32_sw_be(crc, buf, len);
#else
	return crc32_sw_le(crc, buf, len);
#endif
#endif
}