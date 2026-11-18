void copia(char *destino, char *origen) {
  while (*origen != '\0') {
    *destino++ = *origen++;
  }
  *destino = '\0';
}