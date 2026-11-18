void trataCoordenadas(char *coordenadas, int *linha, int *coluna) {
  *coluna = coordenadas[0] - 'a';
  if (coordenadas[3] == '\0' || coordenadas[3] == '\n')
    *linha = coordenadas[2] - '1';
  else
    *linha = (coordenadas[2] - '0') * 10 + (coordenadas[3] - '0') - 1;
}