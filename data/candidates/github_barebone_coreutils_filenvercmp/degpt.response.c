int filenvercmp(char *a,ptrdiff_t alen,char *b,ptrdiff_t blen)

{
  idx_t s1_len;
  idx_t s2_len;
  bool bVar1;
  bool bVar2;
  int local_78;
  int result;
  _Bool one_pass_only;
  idx_t bprefixlen;
  idx_t aprefixlen;
  _Bool bdotdot;
  _Bool adotdot;
  _Bool bdot;
  _Bool adot;
  _Bool bempty;
  _Bool aempty;
  ptrdiff_t blen_local;
  char *b_local;
  ptrdiff_t alen_local;
  char *a_local;
  int local_c;
  
  if (alen < 0) {
    bVar1 = *a != '\0';
  }
  else {
    bVar1 = alen != 0;
  }
  if (blen < 0) {
    bVar2 = *b != '\0';
  }
  else {
    bVar2 = blen != 0;
  }
  if (bVar1) {
    if (!bVar2) {
      local_c = 1;
    }
    else {
      if (*a == '.') {
        if (*b != '.') {
          return -1;
        }
        if (alen < 0) {
          bVar1 = a[1] == '\0';
        }
        else {
          bVar1 = alen == 1;
        }
        if (blen < 0) {
          bVar2 = b[1] == '\0';
        }
        else {
          bVar2 = blen == 1;
        }
        if (bVar1) {
          return -((bVar2 ^ 0xff) & 1);
        }
        if (bVar2) {
          return 1;
        }
        bVar1 = false;
        if (a[1] == '.') {
          if (alen < 0) {
            bVar1 = a[2] == '\0';
          }
          else {
            bVar1 = alen == 2;
          }
        }
        bVar2 = false;
        if (b[1] == '.') {
          if (blen < 0) {
            bVar2 = b[2] == '\0';
          }
          else {
            bVar2 = blen == 2;
          }
        }
        if (bVar1) {
          return -(uint)(bVar2 ^ 1);
        }
        if (bVar2) {
          return 1;
        }
      }
      else if (*b == '.') {
        return 1;
      }
      blen_local = blen;
      b_local = b;
      alen_local = alen;
      a_local = a;
      s1_len = file_prefixlen(a,&alen_local);
      s2_len = file_prefixlen(b_local,&blen_local);
      bVar1 = s1_len != alen_local;
      bVar2 = s2_len != blen_local;
      local_78 = verrevcmp(a_local,s1_len,b_local,s2_len);
      if ((local_78 == 0) && (bVar1 || bVar2)) {
        local_78 = verrevcmp(a_local,alen_local,b_local,blen_local);
      }
      local_c = local_78;
    }
  }
  else {
    local_c = -((!bVar2 ^ 0xff) & 1);
  }
  return local_c;
}