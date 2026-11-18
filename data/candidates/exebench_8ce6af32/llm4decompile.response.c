int endStrider(char *s, int *addend){

  *addend = 0;
  if(strstr(s,"//") != NULL){

    return 1;
  }

  return 0;
}