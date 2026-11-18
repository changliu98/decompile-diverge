int func0(char *password)
{
  int i; int len = strlen(password);
  int hasLower = 0; int hasUpper = 0; int hasDigit = 0; int hasSpecial = 0;
  if (len < 6 || len > 12)
    return 0;
  for (i = 0; i < len; i++)
  {
    if (((*__ctype_b_loc ())[(int) ((password[i]))] & (unsigned short) _ISlower))
      hasLower = 1;
    else if (((*__ctype_b_loc ())[(int) ((password[i]))] & (unsigned short) _ISupper))
      hasUpper = 1;
    else if (((*__ctype_b_loc ())[(int) ((password[i]))] & (unsigned short) _ISdigit))
      hasDigit = 1;
    else if (password[i] == '$' || password[i] == '#' || password[i] == '@')
      hasSpecial = 1;
    else if (((*__ctype_b_loc ())[(int) ((password[i]))] & (unsigned short) _ISspace))
      return 0;
  }
  if (hasLower && hasUpper && hasDigit && hasSpecial)
    return 1;
  return 0;
}