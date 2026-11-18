char pop(char *buffer, int *index)
{
 char ret = -1;
 if (*index < 100 && *index >= 0) {
  ret = buffer[*index];
  (*index)--;
 }
 return ret;
}