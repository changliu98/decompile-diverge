void __cdecl makeSinTable()
{
  int x; // [rsp+0h] [rbp-4h]
  int xa; // [rsp+0h] [rbp-4h]
  int xb; // [rsp+0h] [rbp-4h]
  int xc; // [rsp+0h] [rbp-4h]

  for ( x = 0; x < 256; ++x )
    fullsin_table[x + 256] = fullsin_table[256 - x - 1];
  for ( xa = 0; xa < 512; ++xa )
    fullsin_table[xa + 512] = fullsin_table[xa] | 0x8000;
  for ( xb = 0; xb < 512; ++xb )
    halfsin_table[xb] = fullsin_table[xb];
  for ( xc = 512; xc < 1024; ++xc )
    halfsin_table[xc] = 4095;
}