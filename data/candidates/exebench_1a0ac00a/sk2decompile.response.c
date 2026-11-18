void agrega(int *primero, int *ultimo, int dato, int *siguiente) {
  if (*primero == -1)
    *primero = dato;
  else
    siguiente[*ultimo] = dato;
  *ultimo = dato;
  siguiente[*ultimo] = -1;
}