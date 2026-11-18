#include <regex.h>

// Function checks if the input text matches the regex "^[a-z]+_[a-z]+$"
const char *check_regex_match(const char *text)
{
  regex_t regex;
  int match_result;

  // Compile the regular expression. 
  // The flag '1' corresponds to REG_EXTENDED in <regex.h>
  regcomp(&regex, "^[a-z]+_[a-z]+$", REG_EXTENDED);
  
  // Execute the regular expression.
  // 0 and NULL correspond to nmatch=0 and pmatch=NULL (no match details needed)
  match_result = regexec(&regex, text, 0, NULL, 0);
  
  regfree(&regex);

  // regexec returns 0 on a successful match, and REG_NOMATCH (1) on failure
  if (match_result)
    return "Not matched!";
  else
    return "Found a match!";
}