char *__cdecl itoa(int value, char *str, int base)
{
  char *v3; // rax
  char *v4; // rax
  char *v5; // rax
  char *v6; // rax
  char tmp; // [rsp+1h] [rbp-39h]
  char *low; // [rsp+2h] [rbp-38h]
  char *ptr; // [rsp+Ah] [rbp-30h]
  char *ptra; // [rsp+Ah] [rbp-30h]

  if ( base >= 2 && base <= 36 )
  {
    ptr = str;
    low = str;
    do
    {
      v3 = ptr++;
      *v3 = aZyxwvutsrqponm[value % base + 35];
      value /= base;
    }
    while ( value );
    v4 = ptr;
    ptra = ptr - 1;
    *v4 = 0;
    while ( low < ptra )
    {
      tmp = *low;
      v5 = low++;
      *v5 = *ptra;
      v6 = ptra--;
      *v6 = tmp;
    }
    return str;
  }
  else
  {
    *str = 0;
    return str;
  }
}