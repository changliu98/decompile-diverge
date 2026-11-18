void
ToRNA(char *sequence){

  for (;*sequence; sequence++){
    switch (*sequence){
      case 'T': *sequence = 'U';
                break;
      case 't': *sequence = 'u';
                break;
    }
  }
}