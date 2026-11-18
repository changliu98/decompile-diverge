char * func0(char *text,int n)

{
  int iVar1;
  bool bVar2;
  int start;
  int num_replacements;
  char *pattern;
  regmatch_t pmatch [1];
  regex_t regex;
  int n_local;
  char *text_local;
  
  strcpy(func0::new_text,text);
  regcomp((regex_t *)&regex,"[ ,.]",1);
  num_replacements = 0;
  while( true ) {
    bVar2 = false;
    if (num_replacements < n) {
      iVar1 = regexec((regex_t *)&regex,func0::new_text,1,(regmatch_t *)pmatch,0);
      bVar2 = iVar1 == 0;
    }
    if (!bVar2) break;
    func0::new_text[pmatch[0].rm_so] = ':';
    num_replacements = num_replacements + 1;
  }
  regfree((regex_t *)&regex);
  return func0::new_text;
}