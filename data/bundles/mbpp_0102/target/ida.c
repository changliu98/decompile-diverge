char *__cdecl func0(const char *word, char *output)
{
  char v2; // dl
  int v3; // ecx
  int v4; // ecx
  int capitalize_next; // [rsp+4h] [rbp-1Ch]
  int output_index; // [rsp+8h] [rbp-18h]
  int word_index; // [rsp+Ch] [rbp-14h]

  word_index = 0;
  output_index = 0;
  capitalize_next = 1;
  while ( word[word_index] )
  {
    if ( word[word_index] == 95 )
    {
      capitalize_next = 1;
    }
    else if ( capitalize_next )
    {
      v2 = toupper(word[word_index]);
      v3 = output_index++;
      output[v3] = v2;
      capitalize_next = 0;
    }
    else
    {
      v4 = output_index++;
      output[v4] = word[word_index];
    }
    ++word_index;
  }
  output[output_index] = 0;
  return output;
}