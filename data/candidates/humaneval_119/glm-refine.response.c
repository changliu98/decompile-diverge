const char *__cdecl func0(const char *s1, const char *s2)
{
  int balance;
  int is_valid;
  int len1;
  int len2;
  int i;

  len1 = strlen(s1);
  len2 = strlen(s2);

  // Check if s1 followed by s2 forms a valid parenthesis sequence
  balance = 0;
  is_valid = 1;
  
  for (i = 0; i < len1; ++i)
  {
    if (s1[i] == '(') ++balance;
    if (s1[i] == ')') --balance;
    if (balance < 0) is_valid = 0;
  }
  
  for (i = 0; i < len2; ++i)
  {
    if (s2[i] == '(') ++balance;
    if (s2[i] == ')') --balance;
    if (balance < 0) is_valid = 0;
  }
  
  if (balance == 0 && is_valid)
    return unk_2004;

  // Check if s2 followed by s1 forms a valid parenthesis sequence
  balance = 0;
  is_valid = 1;
  
  for (i = 0; i < len2; ++i)
  {
    if (s2[i] == '(') ++balance;
    if (s2[i] == ')') --balance;
    if (balance < 0) is_valid = 0;
  }
  
  for (i = 0; i < len1; ++i)
  {
    if (s1[i] == '(') ++balance;
    if (s1[i] == ')') --balance;
    if (balance < 0) is_valid = 0;
  }
  
  if (balance == 0 && is_valid)
    return unk_2004;
  else
    return unk_2008;
}