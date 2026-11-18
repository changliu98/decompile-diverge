void
vrna_seq_toRNA(char *sequence,
               int is_dna){

  if(is_dna){
    while(*sequence){
      if(!strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *sequence)){
        if(*sequence == ' ' ||
           *sequence == '.' ||
           *sequence == '_' ||
           *sequence == '-' ||
           *sequence == '~'){
          sequence++;
        }else{
          *sequence = 'N';
        }
      }
      sequence++;
    }
  }else{
    while(*sequence){
      if(!strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *sequence)){
        *sequence = 'N';
      }
      sequence++;
    }
  }
}