int strip_trailing_slashes(char *path)
{
 char *base;
 char *base_lim;
 char *p;
 int had_slash;




 base = last_component(path);
 if (*base == '\0')
  base = path;
 p = base;
 base_lim = p + base_len(base);
 had_slash = (*base_lim != '\0' ? 1 : 0);
 *base_lim = '\0';
 return (had_slash & 1);
}