

void _crc32_final( unsigned int *crc )
{
 *crc = *crc ^ 0xFFFFFFFFUL;
}
