char* list_to_str(int n) {
 int i;
 char* str;
 char* p;
 int len = 2;

 for (i = 1;; i++) {
  if (i > n)
   break;
  len += snprintf(NULL, 0, " %d", i);
 }

 str = malloc(len * sizeof(char));
 if (str == NULL)
  return NULL;

 p = str;
 p += sprintf(p, "0");
 for (i = 1;; i++) {
  if (i > n)
   break;
  p += sprintf(p, " %d", i);
 }

 return str;
}