void set_bit(uint8_t *data,size_t pos)

{
  uint8_t mask;
  size_t pos_local;
  uint8_t *data_local;
  
  data[pos >> 3] = data[pos >> 3] | (byte)(1 << (7 - ((byte)pos & 7) & 0x1f));
  return;
}