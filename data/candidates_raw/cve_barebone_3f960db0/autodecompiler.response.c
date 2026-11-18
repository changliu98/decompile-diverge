char *gf_fgets(char *s, int n, GF_FILE *stream, int unicode_type)
{
 char buf[2048];
 char *ret;
 unsigned int i, j, len;

 memset(s, 0, n);

 ret = gf_fgets(s, n, stream);


 if (!ret) return NULL;


 if (unicode_type<=1)
 {
  char *ptr;
  char out[2048];

  j=0;
  len=(unsigned int)strlen(s);
  for (i=0; i<len; i++)
  {
   if ((unicode_type==0) && (s[i]&0x80))
   {
    if ((s[i+1]&0xC0)!=0x80)
    {
     out[j] = (char) (0xC0 | ((s[i] & 0x3) >> 6));
     j++;
     s[i] &= 0xBF;
    }
    else if ((s[i]&0xE0)==0xC0)
    {
     out[j] = s[i];
     i++;
     j++;
    }
    else if ((s[i]&0xF0)==0xE0)
    {
     out[j] = s[i];
     i++;
     j++;
     out[j] = s[i];
     i++;
     j++;
    }
    else if ((s[i]&0xF8)==0xF0)
    {
     out[j] = s[i];
     i++;
     j++;
     out[j] = s[i];
     i++;
     j++;
     out[j] = s[i];
     i++;
     j++;
    }
    else
    {

     i++;
    }
   }
   else
   {
    out[j] = s[i];
    j++;
    if (j>=2048) break;
   }
  }
  out[j] = 0;
  strcpy(s, out);
  return ret;
 }

 if (unicode_type==2)
 {
  for (i=0;; i+=2)
  {
   char tmp;
   if (!s[i] && !s[i+1]) break;
   tmp = s[i+1];
   s[i+1] = s[i];
   s[i] = tmp;
  }
 }
 else
 {
  char *ptr = s;
  i = gf_utf8_wcstombs(buf, 2048, (unsigned int **) &ptr);
  if (i==-1) i=0;
  buf[i] = 0;
  strcpy(s, buf);
  if (unicode_type==3)
   gf_fgetc(stream);
 }
 return ret;
}