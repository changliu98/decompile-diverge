void break_apart_camelcase(char *input, char *output)
{
  regex_t regex;
  regmatch_t matches[3];
  char buffer[1024];
  char *offset;

  regcomp(&regex, "([a-z])([A-Z])", 1);

  strcpy(buffer, input);
  offset = buffer;
  output[0] = '\0';

  while (1) {
    if (regexec(&regex, offset, 3, matches, 0)) break;

    strncat(output, offset, matches[0].rm_so);
    strcat(output, " ");

    offset += matches[0].rm_eo;
  }

  strcat(output, offset);

  regfree(&regex);
}