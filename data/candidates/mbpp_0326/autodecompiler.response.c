struct func0_word *func0(int argc, char **argv)
{
 int i, j, k, l;
 int found, max, index, nwords;
 char buf[50];
 char *p;
 int len;

 nwords = 0;
 for (i = 0; ; i++) {
  if (i >= argc)
   break;
  p = argv[i];
  len = 0;
  while (*p) {
   if (!((*(*___ctype_b_loc ())[(int) ((*p))]&((unsigned short int) (0x2000))) != 0)) {
    buf[len++] = *p;
   } else {
    if (len > 0) {
     buf[len] = '\0';
     found = 0;
     for (j = 0; j < nwords; j++) {
      if (strcmp(func0_words[j].name, buf) == 0) {
       func0_words[j].count++;
       found = 1;
       break;
      }
     }
     if (!found) {
      strcpy(func0_words[nwords].name, buf);
      func0_words[nwords].count = 1;
      nwords++;
     }
     len = 0;
    }
   }
   p++;
  }
  if (len > 0) {
   buf[len] = '\0';
   found = 0;
   for (j = 0; j < nwords; j++) {
    if (strcmp(func0_words[j].name, buf) == 0) {
     func0_words[j].count++;
     found = 1;
     break;
    }
   }
   if (!found) {
    strcpy(func0_words[nwords].name, buf);
    func0_words[nwords].count = 1;
    nwords++;
   }
  }
 }

 max = 0;
 index = 0;
 for (i = 0; i < nwords; i++) {
  if (func0_words[i].count > max) {
   max = func0_words[i].count;
   index = i;
  }
 }
 return &func0_words[index];
}