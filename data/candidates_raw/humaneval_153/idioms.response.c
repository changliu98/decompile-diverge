void get_strongest_extension(char *class_name, char **extensions, int ext_count, char *output)
{
  int i;
  int j;
  int strength;
  int max_strength = -1000;
  char *strongest = ((void *)0);
  char c;
  for (i = 0; i < ext_count; i++)
  {
    char *extension = extensions[i];
    strength = 0;
    for (j = 0; extension[j]; j++)
    {
      c = extension[j];
      if (c >= 'A' && c <= 'Z')
        strength++;
      if (c >= 'a' && c <= 'z')
        strength--;
    }
    if (strength > max_strength)
    {
      max_strength = strength;
      strongest = extensions[i];
    }
  }
  sprintf(output, "%s.%s", class_name, strongest);
}