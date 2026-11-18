wchar_t archive_string_append_from_wcs(archive_string *as,wchar_t *w,size_t len)

{
  char *pcVar1;
  size_t sVar2;
  archive_string *paVar3;
  size_t sVar4;
  int *piVar5;
  mbstate_t shift_state;
  char *end;
  char *p;
  wchar_t ret_val;
  wchar_t n;
  size_t len_local;
  wchar_t *w_local;
  archive_string *as_local;
  wchar_t local_c;
  
  ret_val = L'\0';
  memset(&shift_state,0,8);
  paVar3 = archive_string_ensure(as,as->length + len + 1);
  if (paVar3 == (archive_string *)0x0) {
    local_c = L'\xffffffff';
  }
  else {
    p = as->s + as->length;
    pcVar1 = as->s;
    sVar2 = as->buffer_length;
    sVar4 = __ctype_get_mb_cur_max();
    end = pcVar1 + (sVar2 - sVar4) + -1;
    w_local = w;
    for (len_local = len; *w_local != L'\0' && len_local != 0; len_local = len_local - 1) {
      if (end <= p) {
        as->length = (long)p - (long)as->s;
        as->s[as->length] = '\0';
        paVar3 = archive_string_ensure(as,as->length + len_local * 2 + 1);
        if (paVar3 == (archive_string *)0x0) {
          return L'\xffffffff';
        }
        p = as->s + as->length;
        pcVar1 = as->s;
        sVar2 = as->buffer_length;
        sVar4 = __ctype_get_mb_cur_max();
        end = pcVar1 + (sVar2 - sVar4) + -1;
      }
      sVar4 = wcrtomb(p,*w_local,(mbstate_t *)&shift_state);
      if ((int)sVar4 == -1) {
        piVar5 = __errno_location();
        if (*piVar5 != 0x54) {
          ret_val = L'\xffffffff';
          break;
        }
        *p = '?';
        ret_val = L'\xffffffff';
        p = p + 1;
      }
      else {
        p = p + (int)sVar4;
      }
      w_local = w_local + 1;
    }
    as->length = (long)p - (long)as->s;
    as->s[as->length] = '\0';
    local_c = ret_val;
  }
  return local_c;
}