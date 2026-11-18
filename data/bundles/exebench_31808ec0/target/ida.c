void __cdecl trataCoordenadas(char *linha, int *horizontal, int *vertical)
{
  *vertical = *linha - 97;
  if ( linha[3] && linha[3] != 10 )
    *horizontal = linha[3] - 48 + 10 * (linha[2] - 48) - 1;
  else
    *horizontal = linha[2] - 49;
}