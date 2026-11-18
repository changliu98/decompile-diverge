void remove_line_ending(char *ptr,char ch)
{
 char *tmp;

 if((tmp=strrchr(ptr,ch)))
 {
  *tmp='\0';
 }
}