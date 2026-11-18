int checkForSpecialChar(char *inputString)
{
 regex_t regex;
 int reti;
 char msgbuf[100];
 int flag = 0;

 regcomp(&regex, "[^a-zA-Z0-9.]", 1);

 reti = regexec(&regex, inputString, 0, NULL, 0);
 if( !reti )
 {
     printf("Matches\n");
 }
 else if( reti == REG_NOMATCH )
 {
     printf("No matches\n");
 }
 else
 {
     regerror(reti, &regex, msgbuf, sizeof(msgbuf));
     fprintf(stderr, "Regex match error: %s\n", msgbuf);
 }

 regfree(&regex);

 return (reti == 1) ? 1 : 0;
}