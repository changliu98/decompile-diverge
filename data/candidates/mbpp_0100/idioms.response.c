int func0(int num)
{
  int i; int j;
  int len; int isPalindrome;
  char numstr[20];
  int ret = num + 1;
  int numa = num;
  for (i = num + 1; i < 0x7fffffff; i++)
  {
    sprintf(numstr,"%d",i);
    len = strlen(numstr);
    isPalindrome = 1;
    for (j = 0; j < len / 2; j++)
    {
      if (numstr[j] != numstr[len - 1 - j])
      {
        isPalindrome = 0;
        break;
      }
    }
    if (isPalindrome)
    {
      ret = i;
      break;
    }
  }
  return ret;
}