int func0(char *bracket_string)
{
 int i;
 int level;
 char err;

 level = 0;
 i = 0;
 while (1) {
  if (bracket_string[i] == '\0') {
   break;
  }
  switch (bracket_string[i]) {
  case '<':
   level++;
   break;
  case '>':
   level--;
   break;
  }
  if (level < 0) {
   err = 1;
   break;
  }
  i++;
 }
 if (level != 0) {
  err = 1;
 }

 return ((err & 1) ^ 1);
}