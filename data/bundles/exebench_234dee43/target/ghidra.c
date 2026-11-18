char * utf8_to_ucs4(char *ptr,wchar_t *result)

{
  wchar_t wVar1;
  wchar_t i;
  wchar_t bits_count;
  wchar_t octet_count;
  wchar_t ch;
  wchar_t ret;
  wchar_t *result_local;
  char *ptr_local;
  
  ptr_local = ptr + 1;
  wVar1 = (wchar_t)(byte)*ptr;
  if ((*ptr & 0x80U) == 0) {
    if (result != (wchar_t *)0x0) {
      *result = wVar1;
    }
  }
  else {
    if ((wVar1 & 0xe0U) == 0xc0) {
      octet_count = L'\x02';
      ch = wVar1 & 0xffffff1f;
    }
    else if ((wVar1 & 0xf0U) == 0xe0) {
      octet_count = L'\x03';
      ch = wVar1 & 0xffffff0f;
    }
    else if ((wVar1 & 0xf8U) == 0xf0) {
      octet_count = L'\x04';
      ch = wVar1 & 0xffffff07;
    }
    else if ((wVar1 & 0xfcU) == 0xf8) {
      octet_count = L'\x05';
      ch = wVar1 & 0xffffff03;
    }
    else {
      if ((wVar1 & 0xfeU) != 0xfc) {
        return (char *)0x0;
      }
      octet_count = L'\x06';
      ch = wVar1 & 0xffffff01;
    }
    bits_count = (octet_count + L'\xffffffff') * 6;
    ret = ch << ((byte)bits_count & 0x1f);
    for (i = L'\x01'; i < octet_count; i = i + L'\x01') {
      bits_count = bits_count + L'\xfffffffa';
      if (((byte)*ptr_local & 0xc0) != 0x80) {
        return (char *)0x0;
      }
      ret = ((byte)*ptr_local & 0x3f) << ((byte)bits_count & 0x1f) | ret;
      ptr_local = ptr_local + 1;
    }
    if (result != (wchar_t *)0x0) {
      *result = ret;
    }
  }
  return ptr_local;
}