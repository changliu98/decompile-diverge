int check_first(char *str)
{
 regex_t regex;
 int reti;
 char buff[50];
 char *ptr;
 char result;

 reti = regcomp(&regex, "^5", 0);
 if( reti ) {
     fprintf(stderr, "Could not compile regex\n");
     result = 0;
 } else {

     reti = regexec(&regex, str, 0, NULL, 0);
     regfree(&regex);
     if( !reti ) {
         result = 1;
     } else {
         result = 0;
     }
 }

 return (result & 1);
}