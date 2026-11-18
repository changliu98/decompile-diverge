static int
validate_tag_name(char *tag, size_t len)
{
 size_t i;
 int ret;

 if (len == 1 && tag[0] == '.')
  ret = 0;
 else if (tag[0] == '.' || tag[len-1] == '.')
  ret = -1;
 else {
  for (i = 0; i < len; i++) {
   if (tag[i] == ' ' || tag[i] == '\t' ||
       tag[i] == '\v' || tag[i] == '\f')
    return -1;
   if (tag[i] == '.' && i+1 < len && tag[i+1] == '.')
    return -1;
  }
  ret = 0;
 }

 return ret;
}