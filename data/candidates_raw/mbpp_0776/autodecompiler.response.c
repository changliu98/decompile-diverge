int
str_vowel_count(char *s)
{
 int i;
 int len;
 int count = 0;
 char *vowels = "aeiou";

 len = strlen(s);

 for (i = 1; ; i++) {
  if (i >= len-1) {
   break;
  }
  if (strchr(vowels, s[i]) != NULL) {
   continue;
  }
  if ((strchr(vowels, s[i-1]) != NULL) ||
      (strchr(vowels, s[i+1]) != NULL)) {
   count++;
  }
 }

 if (strchr(vowels, s[0]) == NULL && strchr(vowels, s[1]) != NULL) {
  count++;
 }
 if (strchr(vowels, s[len-1]) == NULL && strchr(vowels, s[len-2]) != NULL) {
  count++;
 }

 return count;
}