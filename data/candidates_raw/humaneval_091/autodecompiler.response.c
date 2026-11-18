int irc_IsChannel(char *string) {
 int i, chans, ischan, start;
 ischan = 1;
 i = 0;
 chans = 0;
 start = 0;
 while (1) {
  if (string[i] == '\0') break;
  if ((((((((unsigned short int) *(*(___ctype_b_loc () + (string[i])))) & (unsigned short int) 8192)) != 0)) && start) ) {
   start = 0;
   chans++;
  }
  if (string[i] == 'I' && ischan) start = 1;
  else if (!((((((unsigned short int) *(*(___ctype_b_loc () + (string[i])))) & (unsigned short int) 8192)) != 0))) start = 0;
  if (((((unsigned short int) *(*(___ctype_b_loc () + (string[i])))) & (unsigned short int) 8192)) == 0) ischan = 0;
  if (string[i] == '.' || string[i] == '?' || string[i] == '!') ischan = 1;
  i++;
 }
 return chans;
}