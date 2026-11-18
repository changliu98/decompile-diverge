void leer_datos_instruccion(unsigned char b1, unsigned char b2, int *op,
                            int *dir, int *tipo) {
  *tipo = 0;
  if (((b1 >> 2) % 2) == 1) {
    *tipo = 1;
  }
  *op = b1 >> 3;
  *dir = (b1 % 4) * 256 + b2;
}