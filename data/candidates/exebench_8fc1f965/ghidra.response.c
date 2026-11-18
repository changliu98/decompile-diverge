void murcielagoCrypt(char *str)

{
  int letterIndex;
  int strIndex;
  char *to;
  char *from;
  char *str_local;
  
  strIndex = 0;
  do {
    if (str[strIndex] == '\0') {
      return;
    }
    for (letterIndex = 0; "MURCIELAGOmurcielago"[letterIndex] != '\0'; letterIndex = letterIndex + 1
        ) {
      if (str[strIndex] == "MURCIELAGOmurcielago"[letterIndex]) {
        str[strIndex] = "01234567890123456789"[letterIndex];
        break;
      }
    }
    strIndex = strIndex + 1;
  } while( true );
}