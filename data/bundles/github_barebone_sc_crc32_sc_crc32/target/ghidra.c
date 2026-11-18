uint32_t sc_crc32(uint32_t crc,void *buf,size_t len)

{
  uint32_t uVar1;
  size_t len_local;
  void *buf_local;
  uint32_t crc_local;
  
  uVar1 = crc32_sw_le(crc,buf,len);
  return uVar1;
}