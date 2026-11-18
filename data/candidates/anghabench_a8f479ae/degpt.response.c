uint calculate_txd_usage(uint buffer_size)
{
  return (buffer_size * 0x55 >> 0x14) + 1;
}