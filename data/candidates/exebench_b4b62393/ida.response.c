void __cdecl intercambiar(int *pos1, int *pos2)
{
  int aux; // [rsp+0h] [rbp-14h]

  if ( pos1 != pos2 )
  {
    aux = *pos1;
    *pos1 = *pos2;
    *pos2 = aux;
  }
}