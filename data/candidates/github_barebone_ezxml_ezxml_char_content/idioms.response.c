void ezxml_char_content(struct ezxml_root *root, char *text, unsigned long len, char is_entity)
{
  struct ezxml *cur = root->cur;
  char *newtext;
  unsigned long newlen;
  unsigned long oldlen;
  if (cur == ((void *)0) || cur->name == ((void *)0) || len == 0)
    return;
  text[len] = '\0';
  newtext = ezxml_entity_replace(text, root->ent, is_entity);
  newlen = ezxml_strlen(newtext) + 1;
  if (cur->txt == ((void *)0))
  {
    cur->txt = newtext;
    return;
  }
  oldlen = ezxml_strlen(cur->txt);
  if (cur->flags & 0x00000040)
  {
    char *newtxt = ezxml_strndup(cur->txt, newlen + oldlen);
    cur->txt = newtxt;
  }
  else
  {
    char *newtxt = ezxml_strndup(newlen + oldlen);
    newtxt = ezxml_strconcat(newtxt, cur->txt);
    cur->txt = newtxt;
  }
  cur->txt = ezxml_strconcat(cur->txt + oldlen, newtext);
  if (newtext != text)
    ezxml_strfree(newtext);
  if (cur->txt != text)
    ezxml_set_flag(cur, 0x00000040);
}