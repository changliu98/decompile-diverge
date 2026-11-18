int func0(char *num)
{
 int i, count = 0;
 for (i = 0; i < strlen(num); i++)
  if (strchr("2357BD", num[i]))
   count++;
 return count;
}