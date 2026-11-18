char *func0(char *s, char *buf)
{
 int i,j;
 int space_len=0;

 j=0;
 for(i=0;;i++) {
  if (i>=strlen(s)) break;
  if (s[i]==' ') {
   space_len++;
   continue;
  }
  if (space_len==1) buf[j++]='_';
  if (space_len==2) { buf[j++]='*'; buf[j++]='*'; }
  if (space_len>2) buf[j++]='-';
  space_len=0;
  buf[j++]=s[i];
 }
 if (space_len==1) buf[j++]='_';
 if (space_len==2) { buf[j++]='*'; buf[j++]='*'; }
 if (space_len>2) buf[j++]='-';
 buf[j]=0;
 return buf;
}