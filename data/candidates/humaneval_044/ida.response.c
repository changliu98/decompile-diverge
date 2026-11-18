void __cdecl func0(int x, int base, char *out)
{
  int v3; // eax
  int v4; // ecx
  int j; // [rsp+0h] [rbp-44h]
  char temp[33]; // [rsp+4h] [rbp-40h]
  int index; // [rsp+30h] [rbp-14h]
  char *outa; // [rsp+34h] [rbp-10h]
  int basea; // [rsp+3Ch] [rbp-8h]
  int xa; // [rsp+40h] [rbp-4h]

  xa = x;
  basea = base;
  outa = out;
  index = 0;
  while ( xa > 0 )
  {
    v3 = index++;
    temp[v3] = xa % basea + 48;
    xa /= basea;
  }
  j = 0;
  while ( index > 0 )
  {
    --index;
    v4 = j++;
    outa[v4] = temp[index];
  }
  outa[j] = 0;
}