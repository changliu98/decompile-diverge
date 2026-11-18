char** extractFunction2(char* input, int* size) {
  char regex_raw[] = "[a-zA-Z0-9\\_]+";
  regex_t regex;
  regmatch_t matches[1];
  int match_start, match_end;
  int i = 0;

  char input_copy[strlen(input)+1];
  strcpy(input_copy, input);

  regcomp(&regex, regex_raw, 1);
  char* p = input_copy;
  while (1) {
    if (regexec(&regex, p, 1, matches, 0)) break;
    match_start = matches[0].rm_so;
    match_end = matches[0].rm_eo;
    char* new_string = (char*) malloc(match_end-match_start+1);
    strncpy(new_string, p+match_start, match_end-match_start);
    new_string[match_end-match_start] = '\0';
    func2.words[i++] = new_string;
    p += match_end;
  }
  regfree(&regex);
  *size = i;
  return func2.words;
}