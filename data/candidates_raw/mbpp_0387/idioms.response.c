char *isEven(char *num)
{
  int len = strlen(num);
  if (num[len-1] == '0' || num[len-1] == '2' || num[len-1] == '4' || num[len-1] == '6' || num[len-1] == '8'|| num[len-1] == 'A'|| num[len-1] == 'C'|| num[len-1] == 'E')
  {
    return "Even";
  }
  else
  {
    return "Odd";
  }
}