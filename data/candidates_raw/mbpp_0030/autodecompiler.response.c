int get_max_num_of_repetition(char *str)
{
 int i,j;
 int len = strlen(str);
 int count = 0;

 for(i=0;i<len;i++)
 {
  for(j=1;j<=len-i;j++)
  {

   if(check_Equality(str,i,j))
   {
    count++;
   }
  }
 }

 return count;
}