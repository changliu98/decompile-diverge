char *__cdecl func0(const char *email)
{
  int ret; // [rsp+4h] [rbp-5Ch]
  regex_t regex; // [rsp+8h] [rbp-58h] BYREF
  const char *regex_pattern; // [rsp+48h] [rbp-18h]
  const char *emaila; // [rsp+50h] [rbp-10h]

  emaila = email;
  regex_pattern = "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$";
  if ( regcomp(&regex, "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$", 9) )
    return "Invalid Email";
  ret = regexec(&regex, emaila, 0LL, 0LL, 0);
  regfree(&regex);
  if ( ret )
    return "Invalid Email";
  else
    return "Valid Email";
}