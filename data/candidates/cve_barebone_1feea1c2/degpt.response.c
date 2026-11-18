char * build_ustar_entry_name(char *dest,char *src,size_t src_length,char *insert)

{
  char *pcVar1;
  bool bVar2;
  long lVar3;
  size_t sVar4;
  char *pcVar5;
  bool bVar6;
  size_t insert_length;
  size_t suffix_length;
  int need_slash;
  char *p;
  char *filename_end;
  char *filename;
  char *suffix_end;
  char *suffix;
  char *prefix_end;
  char *prefix;
  char *insert_local;
  size_t src_length_local;
  char *src_local;
  char *dest_local;
  
  bVar2 = false;
  suffix_length = 99;
  if (insert == (char *)0x0) {
    insert_length = 0;
  }
  else {
    sVar4 = strlen(insert);
    insert_length = sVar4 + 2;
  }
  if ((src_length < 100) && (insert == (char *)0x0)) {
    strncpy(dest,src,src_length);
    dest[src_length] = '\0';
  }
  else {
    filename_end = src + src_length;
    while( true ) {
      for (; (src < filename_end && (filename_end[-1] == '/')); filename_end = filename_end + -1) {
        bVar2 = true;
      }
      if (((filename_end <= src + 1) || (filename_end[-1] != '.')) || (filename_end[-2] != '/'))
      break;
      filename_end = filename_end + -2;
      bVar2 = true;
    }
    pcVar5 = filename_end;
    if (bVar2) {
      suffix_length = 0x62;
    }
    do {
      pcVar1 = pcVar5;
      filename = pcVar1 + -1;
      bVar6 = false;
      if (src < filename) {
        bVar6 = *filename != '/';
      }
      pcVar5 = filename;
    } while (bVar6);
    if ((*filename == '/') && (filename < filename_end + -1)) {
      filename = pcVar1;
    }
    lVar3 = suffix_length - insert_length;
    if (filename + lVar3 < filename_end) {
      filename_end = filename + lVar3;
    }
    prefix_end = src + 0x9b;
    if (filename < prefix_end) {
      prefix_end = filename;
    }
    while( true ) {
      bVar6 = false;
      if (src < prefix_end) {
        bVar6 = *prefix_end != '/';
      }
      if (!bVar6) break;
      prefix_end = prefix_end + -1;
    }
    if ((prefix_end < filename) && (*prefix_end == '/')) {
      prefix_end = prefix_end + 1;
    }
    suffix_end = prefix_end + (lVar3 - ((long)filename_end - (long)filename));
    if (filename < suffix_end) {
      suffix_end = filename;
    }
    if (suffix_end < prefix_end) {
      suffix_end = prefix_end;
    }
    while( true ) {
      bVar6 = false;
      if (prefix_end < suffix_end) {
        bVar6 = *suffix_end != '/';
      }
      if (!bVar6) break;
      suffix_end = suffix_end + -1;
    }
    if ((suffix_end < filename) && (*suffix_end == '/')) {
      suffix_end = suffix_end + 1;
    }
    p = dest;
    if (src < prefix_end) {
      strncpy(dest,src,(long)prefix_end - (long)src);
      p = dest + ((long)prefix_end - (long)src);
    }
    if (prefix_end < suffix_end) {
      strncpy(p,prefix_end,(long)suffix_end - (long)prefix_end);
      p = p + ((long)suffix_end - (long)prefix_end);
    }
    if (insert != (char *)0x0) {
      strcpy(p,insert);
      sVar4 = strlen(insert);
      pcVar5 = p + sVar4;
      p = pcVar5 + 1;
      *pcVar5 = '/';
    }
    strncpy(p,filename,(long)filename_end - (long)filename);
    pcVar5 = p + ((long)filename_end - (long)filename);
    p = pcVar5;
    if (bVar2) {
      p = pcVar5 + 1;
      *pcVar5 = '/';
    }
    *p = '\0';
  }
  return dest;
}