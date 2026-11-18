void __cdecl func0(char *input, char *output)
{
  int i; // [rsp+Ch] [rbp-14h]

  for ( i = 0; input[i]; ++i )
    output[i] = tolower((unsigned __int8)input[i]);
  output[i] = 0;
}