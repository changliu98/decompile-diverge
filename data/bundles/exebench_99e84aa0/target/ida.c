char *__cdecl xtoa(unsigned __int64 v, char *string, int r, int is_neg)
{
  char *v4; // rax
  char *v5; // rax
  char *v6; // rax
  char v7; // cl
  char *v8; // rax
  char *p; // [rsp+0h] [rbp-58h]
  char buf[33]; // [rsp+8h] [rbp-50h] BYREF
  char *start; // [rsp+38h] [rbp-20h]
  int is_nega; // [rsp+40h] [rbp-18h]
  int ra; // [rsp+44h] [rbp-14h]
  char *stringa; // [rsp+48h] [rbp-10h]
  unsigned __int64 va; // [rsp+50h] [rbp-8h]

  va = v;
  stringa = string;
  ra = r;
  is_nega = is_neg;
  start = string;
  p = buf;
  do
  {
    v4 = p++;
    *v4 = a0123456789abcd[(va % ra) & 0xF];
    va /= (unsigned __int64)ra;
  }
  while ( va );
  if ( is_nega )
  {
    v5 = p++;
    *v5 = 45;
  }
  do
  {
    v6 = p--;
    v7 = *(v6 - 1);
    v8 = stringa++;
    *v8 = v7;
  }
  while ( buf != p );
  *stringa = 0;
  return start;
}