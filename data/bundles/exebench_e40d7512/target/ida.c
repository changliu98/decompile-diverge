char *__cdecl scnline(int key, char *p, int c)
{
  char *v3; // rax
  char v5; // [rsp+0h] [rbp-1Ch]
  int scnwidth; // [rsp+4h] [rbp-18h]

  scnwidth = 8;
  while ( --scnwidth )
  {
    key *= 2;
    if ( (key & 0x80) != 0 )
      v5 = c;
    else
      v5 = 32;
    v3 = p++;
    *v3 = v5;
  }
  return p;
}