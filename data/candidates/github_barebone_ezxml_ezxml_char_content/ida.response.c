void __cdecl ezxml_char_content(ezxml_root_t root, char *s, size_t len, char t)
{
  char *v4; // rdi
  char *v5; // [rsp+10h] [rbp-40h]
  size_t l; // [rsp+18h] [rbp-38h]
  ezxml_t xml; // [rsp+28h] [rbp-28h]
  size_t lena; // [rsp+38h] [rbp-18h]
  char *sa; // [rsp+40h] [rbp-10h]

  xml = root->cur;
  if ( xml && xml->name && len )
  {
    s[len] = 0;
    sa = ezxml_decode(s, root->ent, t);
    lena = strlen(sa) + 1;
    if ( *xml->txt )
    {
      l = strlen(xml->txt);
      if ( (xml->flags & 0x40) != 0 )
      {
        v5 = (char *)realloc(xml->txt, lena + l);
      }
      else
      {
        v4 = (char *)malloc(lena + l);
        v5 = strcpy(v4, xml->txt);
      }
      xml->txt = v5;
      strcpy(&xml->txt[l], sa);
      if ( sa != s )
        free(sa);
    }
    else
    {
      xml->txt = sa;
    }
    if ( xml->txt != s )
      ezxml_set_flag(xml, 64);
  }
}