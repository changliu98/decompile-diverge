void squeeze_all(char s1[], char s2[])
{
 int badchar = 0;
 int j, k, l;

 for (j=0, l=0; s1[j] != '\0'; j++)
 {
  badchar = 0;
  for (k=0; s2[k] != '\0'; k++)
  {
   if (s1[j] == s2[k])
    badchar = 1;
  }
  if (!badchar)
   s1[l++] = s1[j];
 }
 s1[l] = '\0';
}