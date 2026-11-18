void func0(char *input,char *output)

{
  int iVar1;
  int i;
  char *output_local;
  char *input_local;
  
  for (i = 0; input[i] != '\0'; i = i + 1) {
    iVar1 = tolower((uint)(byte)input[i]);
    output[i] = (char)iVar1;
  }
  output[i] = '\0';
  return;
}