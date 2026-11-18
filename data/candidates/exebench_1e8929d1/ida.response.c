void __cdecl convert2ASCII(char input, char *output)
{
  unsigned __int8 temp; // [rsp+1h] [rbp-11h]
  char inputa; // [rsp+11h] [rbp-1h]

  temp = input >> 4;
  if ( (unsigned __int8)(input >> 4) >= 0xAu )
    *output = temp - 10 + 97;
  else
    *output = temp + 48;
  inputa = input & 0xF;
  if ( (input & 0xF) >= 10 )
    output[1] = inputa - 10 + 97;
  else
    output[1] = inputa + 48;
}