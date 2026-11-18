char *x_basename(char *path)
{
 char *p, *last, *found_slash = path;

 for (p = path; ; p++)
 {
  if (*p == '/')
  {
   found_slash = p;
   continue;
  }
  if (!*p)
   break;
  if (*p != '/')
  {
   if (found_slash)
   {
    last = p;
    found_slash = NULL;
   }
   continue;
  }
 }

 return last;
}