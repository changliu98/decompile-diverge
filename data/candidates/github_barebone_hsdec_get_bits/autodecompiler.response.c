unsigned short get_bits(struct SPI *spi, unsigned char bitlen)
{
 unsigned short ret;
 int i;

 ret = 0;
 i = 0;

 if (bitlen > 15)
  return 0xffff;

 if (spi->rx_len == 0 && spi->rx_bit < (1 << (bitlen - 1)))
  return 0xffff;

 while (1) {
  if (i >= bitlen)
   break;

  if (spi->rx_bit == 0) {
   if (spi->rx_len == 0)
    return 0xffff;
   else
    spi->rx_byte = spi->rx_buf[spi->rx_idx++];

   if (spi->rx_idx == spi->rx_len) {
    spi->rx_idx = 0;
    spi->rx_len = 0;
   }
   spi->rx_bit = 0x80;
  }

  ret <<= 1;
  if (spi->rx_byte & spi->rx_bit)
   ret |= 1;
  spi->rx_bit >>= 1;
  i++;
 }

 return ret;
}