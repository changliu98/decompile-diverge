int count(char *str, size_t *max)
{
 char *tmp = strchr(str, '\0');
 int words = 0;
 int gui = 0;
 size_t lenght_current = 0;
 size_t lenght_max = 0;

 tmp--;
 while (1) {
  if (*tmp == ' ') {
   *tmp = '\0';
   tmp--;
  } else {
   break;
  }
 }

 tmp = str;

 while (1) {
  if (*tmp == ' ') {
   tmp++;
  } else {
   break;
  }
 }

 if (*tmp != '\0') {
  words++;
 }

 while (1) {

  if (*tmp == '\0') {
   if (lenght_current > lenght_max) {
    lenght_max = lenght_current;
   }
   *max = lenght_max;
   return words;
  }

  if (*tmp == '"' || *tmp == '\'') {
   gui = (gui) ? 0 : 1;
  }

  if (*tmp == ' ' && !gui) {
   if (lenght_current > lenght_max) {
    lenght_max = lenght_current;
   }
   lenght_current = 0;
   words++;
   while (1) {
    if (*tmp == ' ') {
     tmp++;
    } else {
     tmp--;
     break;
    }
   }
  } else {
   lenght_current++;
  }
  tmp++;
 }
}