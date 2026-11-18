void
vrna_seq_toRNA(char *sequence){

  for (;*sequence; sequence++){
    switch (*sequence){
      case 'T': *sequence = 'U';
                break;
      case 't': *sequence = 'u';
                break;
    }
  }
}