char *func0(char *word, char *result)
{
 int i, j, capitalize;

 i = j = 0;
 capitalize = 1;
 while (word[i] != '\0') {
  if (word[i] == '_') {
   capitalize = 1;
   i++;
   continue;
  }

  if (capitalize) {
   result[j++] = toupper(word[i++]);
   capitalize = 0;
  } else {
   result[j++] = word[i++];
  }
 }
 result[j] = '\0';

 return result;
}