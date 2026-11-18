int __cdecl ltos(char *s, long num)
{
  char *v2; // rax
  char *v3; // rax
  char *v4; // rax
  char *v5; // rax
  char v6; // cl
  char *v7; // rax
  long v9; // [rsp+0h] [rbp-48h]
  unsigned __int64 anum; // [rsp+8h] [rbp-40h]
  char *p; // [rsp+10h] [rbp-38h]
  char buf[20]; // [rsp+18h] [rbp-30h] BYREF
  long numa; // [rsp+38h] [rbp-10h]
  char *sa; // [rsp+40h] [rbp-8h]

  sa = s;
  numa = num;
  p = buf;
  if ( num >= 0 )
    v9 = numa;
  else
    v9 = -numa;
  for ( anum = v9; anum > 9; anum /= 0xAuLL )
  {
    v2 = p++;
    *v2 = anum % 0xA + 48;
  }
  if ( numa < 0 )
  {
    v3 = sa++;
    *v3 = 45;
  }
  v4 = sa++;
  *v4 = anum + 48;
  while ( 1 )
  {
    v5 = p--;
    if ( v5 <= buf )
      break;
    v6 = *p;
    v7 = sa++;
    *v7 = v6;
  }
  *sa = 0;
  return 0;
}