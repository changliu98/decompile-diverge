int __cdecl ExtractRnick(char *Rnick, char *incoming_msg)
{
  bool v3; // [rsp+1h] [rbp-1Dh]
  int k; // [rsp+2h] [rbp-1Ch]
  char *incoming_msga; // [rsp+6h] [rbp-18h]

  incoming_msga = incoming_msg;
  k = 0;
  if ( *incoming_msg == 58 )
    incoming_msga = incoming_msg + 1;
  while ( 1 )
  {
    v3 = 0;
    if ( *incoming_msga != 33 )
      v3 = *incoming_msga != 0;
    if ( !v3 )
      break;
    Rnick[k++] = *incoming_msga++;
  }
  Rnick[k] = 0;
  return *Rnick >= 48;
}