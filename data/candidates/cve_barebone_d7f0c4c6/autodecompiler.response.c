char *gf_text_get_utf8_line(char *s, int n, GF_FILE *stream, int unicode_type)
{
 char *ret;
 unsigned int i, j, len;
 char buf[2048];
 memset(s, 0, n);
 ret = gf_text_get_utf8_line(s, n, stream);

 if (!ret) return NULL;

 if (unicode_type<=1)
 {
  j=0;
  len=(unsigned int)strlen(s);
  for (i=0; i<len; i++)
  {
   if ((unicode_type==0) && (s[i]&0x80))
   {
    if ((s[i+1]&0xC0)!=0x80)
    {
     if (j>=2048) break;
     buf[j]=(char)(0xC0|((s[i]>>6)&0x3));
     j++;
     s[i]&=0xBF;
    }
    else if ((s[i]&0xE0)==0xC0)
    {
     if (j>=2048) break;
     buf[j]=s[i];
     i++;
     j++;
    }
    else if ((s[i]&0xF0)==0xE0)
    {
     if (j+1>=2048) break;
     buf[j]=s[i];
     i++;
     j++;
     buf[j]=s[i];
     i++;
     j++;
    }
    else if ((s[i]&0xF8)==0xF0)
    {
     if (j+2>=2048) break;
     buf[j]=s[i];
     i++;
     j++;
     buf[j]=s[i];
     i++;
     j++;
     buf[j]=s[i];
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
    if (j>=2048) break;
    buf[j]=s[i];
    j++;
   }
  }
  if (j<2048)
  {
   while (j<2048) buf[j++]=' ';
  }
  else
  {
   while (j<2048) j--;
  }
  buf[j]='\0';
  strcpy(s, buf);
 }
 else if (unicode_type==2)
 {
  i=0;
  while (1)
  {
   if (!s[i] && !s[i+1]) break;
   { char _swap_ch__tmp=s[i+1]; s[i+1]=s[i]; s[i]=_swap_ch__tmp; };
   i+=2;
  }
 }
 else
 {
  char *ptr = s;
  i = (unsigned int)gf_utf8_wcstombs(buf, 2048, &ptr);
  if (i==(unsigned int)-1) i=0;
  buf[i] = '\0';
  strcpy(s, buf);
  if (unicode_type==3)
  {
   gf_fgetc(stream);
  }
 }
 return ret;
}