char *func0(char *text1)
{
 char *text2;
 size_t i, j;
 int space_found;

 if (!text1)
  return NULL;

 text2 = malloc(strlen(text1) + 1);
 if (!text2)
  return NULL;

 space_found = 0;
 for (i = 0, j = 0; text1[i] != '\0'; i++) {
  if (text1[i] == ' ') {
   if (!space_found) {
    text2[j] = text1[i];
    space_found = 1;
    j++;
   }
  } else {
   text2[j] = text1[i];
   space_found = 0;
   j++;
  }
 }
 text2[j] = '\0';

 return text2;
}