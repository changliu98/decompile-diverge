bool stringRotation(char s1[], char s2[])
{
 int len1 = strlen(s1);
 int len2 = strlen(s2);


 if (len1 != len2)
 {
  return false;
 }

 char* twos2 = malloc((2*len2+1)*sizeof(char));
 int i=0;
 for (i=0;i<len2;i++)
 {
  strncpy(twos2,s2+i,len2-i);
  strncpy(twos2+len2-i,s2,i);
  twos2[len2] = '\0';
  if (strstr(s1,twos2) != NULL)
  {
   free(twos2);
   return true;
  }
 }
 free(twos2);
 return false;
}