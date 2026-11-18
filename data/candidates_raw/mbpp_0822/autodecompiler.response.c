int check_valid_password(char *password)
{
 int length = strlen(password);
 char valid = 0;
 char has_lower = 0, has_upper = 0, has_digit = 0, has_special = 0;

 if ((length < 7) || (length > 12)) {
  valid = 0;
 } else {
  int i;
  for (i = 0; i < length; i++) {
   if (islower(password[i])) {
    has_lower = 1;
    continue;
   }
   if (isupper(password[i])) {
    has_upper = 1;
    continue;
   }
   if (isdigit(password[i])) {
    has_digit = 1;
    continue;
   }
   if ((password[i] == '$') || (password[i] == '#') || (password[i] == '@')) {
    has_special = 1;
    continue;
   }
   if (isprint(password[i])) {
    valid = 0;
    break;
   }
  }

  valid = (has_lower && has_upper && has_digit && has_special);
 }

 return (valid ? 1 : 0);
}