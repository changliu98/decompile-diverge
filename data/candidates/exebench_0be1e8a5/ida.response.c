void __cdecl short_to_string(char *res, unsigned __int16 s)
{
  unsigned __int16 r; // [rsp+0h] [rbp-Eh]
  unsigned __int16 ra; // [rsp+0h] [rbp-Eh]
  unsigned __int16 rb; // [rsp+0h] [rbp-Eh]
  unsigned __int8 c; // [rsp+3h] [rbp-Bh]
  unsigned __int8 ca; // [rsp+3h] [rbp-Bh]
  unsigned __int8 cb; // [rsp+3h] [rbp-Bh]

  r = 10000 * (s / 10000);
  *res = s / 10000 + 48;
  c = (s - r) / 1000;
  ra = 1000 * c + r;
  res[1] = c + 48;
  ca = (s - ra) / 100;
  rb = 100 * ca + ra;
  res[2] = ca + 48;
  cb = (s - rb) / 10;
  res[3] = cb + 48;
  res[4] = s - (10 * cb + rb) + 48;
  res[5] = 0;
}