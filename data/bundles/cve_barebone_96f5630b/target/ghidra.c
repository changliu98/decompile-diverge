char * vips_utf8_strcasestr(char *haystack_start,char *needle_start,int len_bytes)

{
  gunichar gVar1;
  gunichar gVar2;
  long lVar3;
  size_t sVar4;
  gunichar b;
  gunichar a;
  int i;
  char *haystack_char;
  char *needle_char;
  char *haystack;
  int needle_len_bytes;
  int needle_len;
  int len_bytes_local;
  char *needle_start_local;
  char *haystack_start_local;
  
  lVar3 = g_utf8_strlen(needle_start,-1);
  sVar4 = strlen(needle_start);
  haystack = haystack_start;
  do {
    if ((long)(len_bytes - (int)sVar4) < (long)haystack - (long)haystack_start) {
      return (char *)0x0;
    }
    haystack_char = haystack;
    needle_char = needle_start;
    for (i = 0; i < (int)lVar3; i = i + 1) {
      gVar1 = g_utf8_get_char_validated
                        (haystack_char,(long)(haystack_start + ((long)len_bytes - (long)haystack)));
      gVar2 = g_utf8_get_char_validated(needle_char,-1);
      if ((((gVar1 == 0xffffffff) || (gVar1 == 0xfffffffe)) || (gVar2 == 0xffffffff)) ||
         (gVar2 == 0xfffffffe)) {
        return (char *)0x0;
      }
      if (gVar1 == 0) {
        return (char *)0x0;
      }
      gVar1 = g_unichar_tolower(gVar1);
      gVar2 = g_unichar_tolower(gVar2);
      if (gVar1 != gVar2) break;
      haystack_char = g_utf8_find_next_char(haystack_char,haystack_start + len_bytes);
      needle_char = g_utf8_find_next_char(needle_char,(char *)0x0);
    }
    if (i == (int)lVar3) {
      return haystack;
    }
    haystack = g_utf8_find_next_char(haystack,(char *)0x0);
  } while( true );
}