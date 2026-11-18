void func0(char *class_name, char **extensions, int ext_count, char *output)
{
 int i, j;
 int strength, max_strength;
 char *extension, *strongest;

 max_strength = -1000;
 strongest = NULL;
 for (i = 0; i < ext_count; i++) {
  extension = extensions[i];
  strength = 0;
  for (j = 0; extension[j] != '\0'; j++) {
   if (extension[j] >= 'A' && extension[j] <= 'Z')
    strength++;
   if (extension[j] >= 'a' && extension[j] <= 'z')
    strength--;
  }
  if (strength > max_strength) {
   max_strength = strength;
   strongest = extension;
  }
 }
 sprintf(output, "%s.%s", class_name, strongest);
}