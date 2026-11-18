#include <cstring>

bool __cdecl is_balanced(const char *brackets)
{
  int level = 0;
  int length = strlen(brackets);

  for (int i = 0; i < length; ++i)
  {
    if (brackets[i] == '(')
      ++level;
    if (brackets[i] == ')')
      --level;
      
    // If at any point we have more closing brackets than opening ones
    if (level < 0)
      return false;
  }
  
  // If the level is 0, all opened brackets have been closed
  return level == 0;
}