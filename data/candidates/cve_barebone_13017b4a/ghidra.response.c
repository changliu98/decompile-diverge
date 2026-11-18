int jpeg_size(uchar *data,uint data_size,int *width,int *height)

{
  int iVar1;
  unsigned_short block_length;
  int i;
  int *height_local;
  int *width_local;
  uint data_size_local;
  uchar *data_local;
  
  if ((((((3 < data_size) && (*data == 0xff)) && (data[1] == 0xd8)) &&
       ((data[2] == 0xff && (data[3] == 0xe0)))) &&
      ((i = 4, 10 < data_size && ((data[6] == 'J' && (data[7] == 'F')))))) &&
     ((data[8] == 'I' && ((data[9] == 'F' && (data[10] == '\0')))))) {
    block_length = (ushort)data[4] * 0x100 + (ushort)data[5];
    while ((uint)i < data_size) {
      iVar1 = (uint)block_length + i;
      if (data_size <= iVar1 + 1U) {
        return -1;
      }
      if (data[iVar1] != 0xff) {
        return -1;
      }
      if (data[iVar1 + 1] == 0xc0) {
        *height = (uint)data[iVar1 + 5] * 0x100 + (uint)data[iVar1 + 6];
        *width = (uint)data[iVar1 + 7] * 0x100 + (uint)data[iVar1 + 8];
        return 0;
      }
      i = iVar1 + 2;
      block_length = (ushort)data[i] * 0x100 + (ushort)data[iVar1 + 3];
    }
  }
  return -1;
}