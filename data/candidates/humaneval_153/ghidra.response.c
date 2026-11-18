void func0(char *class_name,char **extensions,int ext_count,char *output)

{
  char cVar1;
  char *pcVar2;
  char chr;
  int j;
  int strength;
  char *extension;
  int i;
  char *strongest;
  int max_strength;
  char *output_local;
  int ext_count_local;
  char **extensions_local;
  char *class_name_local;
  
  max_strength = -1000;
  strongest = (char *)0x0;
  for (i = 0; i < ext_count; i = i + 1) {
    pcVar2 = extensions[i];
    strength = 0;
    for (j = 0; pcVar2[j] != '\0'; j = j + 1) {
      cVar1 = pcVar2[j];
      if (('@' < cVar1) && (cVar1 < '[')) {
        strength = strength + 1;
      }
      if (('`' < cVar1) && (cVar1 < '{')) {
        strength = strength + -1;
      }
    }
    if (max_strength < strength) {
      max_strength = strength;
      strongest = pcVar2;
    }
  }
  sprintf(output,"%s.%s",class_name,strongest);
  return;
}