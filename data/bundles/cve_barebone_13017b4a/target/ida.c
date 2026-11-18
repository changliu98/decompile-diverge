int __cdecl jpeg_size(unsigned __int8 *data, unsigned int data_size, int *width, int *height)
{
  unsigned __int16 block_length; // [rsp+0h] [rbp-2Eh]
  unsigned int i; // [rsp+2h] [rbp-2Ch]
  int ia; // [rsp+2h] [rbp-2Ch]

  if ( data_size > 3 && *data == 255 && data[1] == 216 && data[2] == 255 && data[3] == 224 )
  {
    i = 4;
    if ( data_size > 0xA && data[6] == 74 && data[7] == 70 && data[8] == 73 && data[9] == 70 && !data[10] )
    {
      block_length = data[5] + (data[4] << 8);
      while ( i < data_size )
      {
        ia = i + block_length;
        if ( ia + 1 >= data_size )
          return -1;
        if ( data[ia] != 255 )
          return -1;
        if ( data[ia + 1] == 192 )
        {
          *height = data[ia + 6] + (data[ia + 5] << 8);
          *width = data[ia + 8] + (data[ia + 7] << 8);
          return 0;
        }
        i = ia + 2;
        block_length = data[i + 1] + (data[i] << 8);
      }
    }
  }
  return -1;
}