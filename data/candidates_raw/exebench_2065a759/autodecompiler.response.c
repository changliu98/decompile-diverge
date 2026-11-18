int BASM_Parse_FetchLabelName(char *sname, char *s)
{
 int i;

 while(1)
 {
  if(!(*s))
  {
   *sname=0;
   i=1; break;
  }
  if(*s=='/')
  {
   *sname=0;
   i=2; break;
  }

  *sname=*s;
  sname++; s++;
 }

 return(i);
}