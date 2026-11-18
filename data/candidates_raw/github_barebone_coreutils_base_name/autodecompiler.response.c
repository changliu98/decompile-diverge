char *
last_part(char *path)
{
 char *base = last_component(path);
 size_t baselen, dotslash_len;
 char *result;

 if (*base) {
  baselen = base_len(base);
  baselen += (base[baselen] == '/') ? 1 : 0;
  dotslash_len = 0;
 } else {
  base = path;
  baselen = base_len(base);
  dotslash_len = 0;
 }

 result = ximalloc(dotslash_len + baselen + 1);
 if (dotslash_len) {
  result[0] = '.';
  result[1] = '/';
 }
 memcpy(result + dotslash_len, base, baselen);
 result[dotslash_len + baselen] = '\0';
 return result;
}