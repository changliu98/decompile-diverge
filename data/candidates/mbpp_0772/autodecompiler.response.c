char *func0(char *str, int n)
{
 char tmp[1000];
 strncpy(tmp, str, 1000);
 tmp[999] = '\0';

 char *out;
 out = malloc(strlen(str)+1);
 if(out == NULL) {
  perror("malloc failed");
  exit(1);
 }
 out[0] = '\0';

 char *tok;
 tok = strtok(tmp, " ");
 while(1) {
  if(tok == NULL)
   break;
  if(strlen(tok) != n) {
   strcat(out, tok);
   strcat(out, " ");
  }
  tok = strtok(NULL, " ");
 }
 size_t len = strlen(out);
 if(len > 0 && out[len-1] == ' ')
  out[len-1] = '\0';

 return out;
}