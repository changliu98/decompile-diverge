int checkPalindrome(char *string)
{
 int length = strlen(string);
 int mid = (int)length/2;
 int i, flag = 0;
 for(i = 0; i < mid; i++)
 {
  if(string[i] != string[length-1-i])
  {
   flag = 0;
   break;
  }
  else
   flag = 1;
 }
 if(flag == 1)
  return(1);
 else
  return(0);
}