char * func0(char **strings,int count)

{
  size_t sVar1;
  int current_length;
  int i;
  int longest_length;
  char *out;
  int count_local;
  char **strings_local;
  
  out = "";
  longest_length = 0;
  for (i = 0; i < count; i = i + 1) {
    sVar1 = strlen(strings[i]);
    if (longest_length < (int)sVar1) {
      out = strings[i];
      longest_length = (int)sVar1;
    }
  }
  return out;
}