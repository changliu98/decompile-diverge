char *strrev(char *s)
{
 int i,j;
 char tmp;
 int len;
 int nletter=0;

 len=strlen(s);
 for(j=0; ; j++){
  if(j>=len) break;
  if(((*___ctype_b_loc ())[(unsigned char) ((s[j]))] & (unsigned short int) 1024)){
   if(((*___ctype_b_loc ())[(unsigned char) ((s[j]))] & (unsigned short int) 256))
    s[j]=tolower(s[j]);
   else if(((*___ctype_b_loc ())[(unsigned char) ((s[j]))] & (unsigned short int) 512))
    s[j]=toupper(s[j]);
   continue;
  }
  nletter++;
 }

 if(nletter==len){
  for(i=0; ; i++){
   if(i>=(len/2)) break;
   tmp=s[i];
   s[i]=s[len-i-1];
   s[len-i-1]=tmp;
  }
 }

 return s;
}