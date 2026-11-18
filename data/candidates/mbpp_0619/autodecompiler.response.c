char *func0(char *str)
{
 int i, j, k;
 char str1[1024], str2[1024];

 j = 0;
 k = 0;

 for (i = 0;; i++) {
  if (str[i] == '\0')
   break;

  if (((((*(unsigned short *)___ctype_b_loc ())[(str[i])] & (unsigned short)0x0800)) != 0))
   str1[j++] = str[i];
  else
   str2[k++] = str[i];
 }

 str1[j] = '\0';
 str2[k] = '\0';

 strcat(str2, str1);

 return func0_res;
}