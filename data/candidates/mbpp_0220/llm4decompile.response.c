char *func0(char *text, int n)
{
 regex_t regex;
 regmatch_t pmatch[1];
 int offset;
 int i;

 strcpy(func0::new_text, text);

 regcomp(&regex, "[ ,.]", 1);

 for (i = 0; i < n && !regexec(&regex, func0::new_text, 1, pmatch, 0); i++)
 {
  func0::new_text[pmatch[0].rm_so] = ':';
 }

 regfree(&regex);

 return func0::new_text;
}