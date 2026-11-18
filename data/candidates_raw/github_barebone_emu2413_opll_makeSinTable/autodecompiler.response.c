void init_sintab(void)
{
 int i;

 for (i = 0; i < 256; i++)
  fullsin_table[256 + i] = fullsin_table[256 - i - 1];
 for (i = 0; i < 512; i++)
  fullsin_table[512 + i] = fullsin_table[i] | 0x8000;
 for (i = 0; i < 512; i++)
  halfsin_table[i] = fullsin_table[i];
 for (i = 512; i < 1024; i++)
  halfsin_table[i] = 0xfff;
}