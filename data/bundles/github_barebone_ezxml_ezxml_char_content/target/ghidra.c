void ezxml_char_content(ezxml_root_t root,char *s,size_t len,char t)

{
  ezxml_t xml_00;
  char *__s;
  size_t sVar1;
  char *pcVar2;
  char *local_48;
  size_t l;
  char *m;
  ezxml_t xml;
  char t_local;
  size_t len_local;
  char *s_local;
  ezxml_root_t root_local;
  
  xml_00 = root->cur;
  if (((xml_00 != (ezxml_t)0x0) && (xml_00->name != (char *)0x0)) && (len != 0)) {
    s[len] = '\0';
    __s = ezxml_decode(s,root->ent,t);
    sVar1 = strlen(__s);
    if (*xml_00->txt == '\0') {
      xml_00->txt = __s;
    }
    else {
      if ((xml_00->flags & 0x40U) == 0) {
        l = strlen(xml_00->txt);
        pcVar2 = malloc(l + sVar1 + 1);
        local_48 = strcpy(pcVar2,xml_00->txt);
      }
      else {
        pcVar2 = xml_00->txt;
        l = strlen(xml_00->txt);
        local_48 = realloc(pcVar2,l + sVar1 + 1);
      }
      xml_00->txt = local_48;
      strcpy(xml_00->txt + l,__s);
      if (__s != s) {
        free(__s);
      }
    }
    if (xml_00->txt != s) {
      ezxml_set_flag(xml_00,0x40);
    }
  }
  return;
}