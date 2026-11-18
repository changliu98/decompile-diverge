void minify(char *json)
{
 char *into=json;
 if (!json) return;
 while (*json)
 {
  int c=*json++;
  switch (c)
  {
   case ' ': case '\t': case '\r': case '\n':
    break;
   case '/':
    if (*json=='/') skip_oneline_comment(&json);
    else if (*json=='*') skip_multiline_comment(&json);
    else *into++=c;
    break;
   case '"':
    minify_string(&json,into);
    break;
   default:
    *into++=c;
  }
 }
 *into=0;
}