void makeSinTable(void)
{
 int i;

 for (i = 0; i < 256; i++)
  fullsin_table[i + 256] = fullsin_table[255 - i];

 for (i = 0; i < 512; i++)
  fullsin_table[i + 512] = fullsin_table[i] | 0x8000;

 for (i = 0; i < 512; i++)
  halfsin_table[i] = fullsin_table[i];

 for (i = 512; i < 1024; i++)
  halfsin_table[i] = 0xfff;
}