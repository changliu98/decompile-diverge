char *func0(char *email)
{
 regex_t email_regex;
 int regex_compilation_result;
 char *valid_email_message = "Valid Email";
 char *invalid_email_message = "Invalid Email";
 char *email_pattern = "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$";
 regex_compilation_result = regcomp(&email_regex, email_pattern, 1 | 8);
 if (regex_compilation_result != 0)
 {
  return invalid_email_message;
 }
 regex_compilation_result = regexec(&email_regex, email, 0, NULL, 0);
 regfree(&email_regex);
 if (regex_compilation_result == 0)
 {
  return valid_email_message;
 }
 else
 {
  return invalid_email_message;
 }
}