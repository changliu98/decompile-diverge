char * func0(char **patterns,int pattern_n,char *text)

{
  int iVar1;
  int i;
  int reti;
  regex_t regex;
  char *text_local;
  int pattern_n_local;
  char **patterns_local;
  
  i = 0;
  while( true ) {
    if (pattern_n <= i) {
      return "Not Matched!";
    }
    iVar1 = regcomp((regex_t *)&regex,patterns[i],0);
    if (iVar1 != 0) break;
    iVar1 = regexec((regex_t *)&regex,text,0,(regmatch_t *)0x0,0);
    if (iVar1 == 0) {
      regfree((regex_t *)&regex);
      return "Matched!";
    }
    regfree((regex_t *)&regex);
    i = i + 1;
  }
  fprintf(*(FILE **)PTR_stderr_00103ff8,"Could not compile regex\n");
  return "Not Matched!";
}