char * func0(char *word,char *output)

{
  bool bVar1;
  int iVar2;
  int capitalize_next;
  int output_index;
  int word_index;
  char *output_local;
  char *word_local;
  
  output_index = 0;
  bVar1 = true;
  for (word_index = 0; word[word_index] != '\0'; word_index = word_index + 1) {
    if (word[word_index] == '_') {
      bVar1 = true;
    }
    else {
      if (bVar1) {
        iVar2 = toupper((int)word[word_index]);
        output[output_index] = (char)iVar2;
        bVar1 = false;
      }
      else {
        output[output_index] = word[word_index];
      }
      output_index = output_index + 1;
    }
  }
  output[output_index] = '\0';
  return output;
}