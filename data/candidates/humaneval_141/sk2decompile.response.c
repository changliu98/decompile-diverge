char* isValid(char* name) {
  int i;
  int len;
  int num;
  int dot;
  char first;
  char* ext;
  num = 0;
  dot = 0;
  len = strlen(name);
  if (len < 5) return "No";
  first = name[0];
  if (first < 'A' || (first > 'Z' && first < 'a') || first > 'z') return "No";
  ext = name + len - 4;
  if (strcmp(ext, ".txt") != 0 && strcmp(ext, ".exe") != 0 &&
      strcmp(ext, ".dll") != 0)
    return "No";
  for (i = 0; i < len; i++) {
    if (name[i] >= '0' && name[i] <= '9') num++;
    if (name[i] == '.') dot++;
  }
  if (num > 3 || dot != 1) return "No";
  return "Yes";
}