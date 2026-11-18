char * url_canonize2(char *d,char *s,size_t n,uint syn33,uint m32,uint m64,uint m96)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  uint local_6c;
  uint local_68;
  uint local_50;
  uint local_4c;
  uchar h2;
  uchar h1;
  uchar c;
  size_t i;
  uint m64_local;
  uint m32_local;
  uint syn33_local;
  size_t n_local;
  char *s_local;
  char *d_local;
  
  i = 0;
  d_local = d;
  if (d == s) {
    for (; (s[i] != '\0' && i < n && (s[i] != '%')); i = i + 1) {
      d_local = d_local + 1;
    }
  }
  do {
    if (s[i] == '\0' || n <= i) {
      *d_local = '\0';
      return d_local;
    }
    bVar3 = s[i];
    if (bVar3 == 0x25) {
      h1 = s[i + 1];
      if (h1 == 0) {
        *d_local = '\0';
        return (char *)0x0;
      }
      h2 = s[i + 2];
      if (((((h1 < 0x30) || (0x39 < h1)) && ((h1 < 0x41 || (0x46 < h1)))) &&
          ((h1 < 0x61 || (0x66 < h1)))) ||
         (((h2 < 0x30 || (0x39 < h2)) &&
          (((h2 < 0x41 || (0x46 < h2)) && ((h2 < 0x61 || (0x66 < h2)))))))) {
        *d_local = '\0';
        return (char *)0x0;
      }
      if (h1 < 0x61) {
        cVar1 = '\0';
        if (0x40 < h1) {
          cVar1 = '7';
        }
      }
      else {
        cVar1 = 'W';
      }
      if (h2 < 0x61) {
        cVar2 = '0';
        if (0x40 < h2) {
          cVar2 = '7';
        }
      }
      else {
        cVar2 = 'W';
      }
      bVar3 = (h1 - cVar1) * '\x10' | h2 - cVar2;
      if ((0x20 < bVar3) && (bVar3 < 0x7f)) {
        if (bVar3 < 0x40) {
          local_68 = m32 & 1 << (0x3f - bVar3 & 0x1f);
        }
        else {
          if (bVar3 < 0x60) {
            local_6c = m64 & 1 << (0x5f - bVar3 & 0x1f);
          }
          else {
            local_6c = m96 & 1 << (0x7f - bVar3 & 0x1f);
          }
          local_68 = local_6c;
        }
        if (local_68 == 0) {
          *d_local = bVar3;
          i = i + 2;
          goto LAB_00101856;
        }
      }
      if (0x60 < h1) {
        h1 = h1 - 0x20;
      }
      if (0x60 < h2) {
        h2 = h2 - 0x20;
      }
      *d_local = '%';
      d_local[1] = h1;
      d_local[2] = h2;
      d_local = d_local + 2;
      i = i + 2;
    }
    else {
      if ((syn33 & 1 << (bVar3 - 0x21 & 0x1f)) == 0) {
        if ((bVar3 < 0x21) || (0x7e < bVar3)) {
          return (char *)0x0;
        }
        if (bVar3 < 0x40) {
          local_4c = m32 & 1 << (0x3f - bVar3 & 0x1f);
        }
        else {
          if (bVar3 < 0x60) {
            local_50 = m64 & 1 << (0x5f - bVar3 & 0x1f);
          }
          else {
            local_50 = m96 & 1 << (0x7f - bVar3 & 0x1f);
          }
          local_4c = local_50;
        }
        if (local_4c != 0) {
          return (char *)0x0;
        }
      }
      *d_local = bVar3;
    }
LAB_00101856:
    d_local = d_local + 1;
    i = i + 1;
  } while( true );
}