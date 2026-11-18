char* mystrncpy(char *dest, char *src, int n) {
 int i;
 char *temp = dest;
 for (i = 0; i < n && *src ; i++)
  *dest++ = *src++;
 *dest = '\0';
 return temp;
}