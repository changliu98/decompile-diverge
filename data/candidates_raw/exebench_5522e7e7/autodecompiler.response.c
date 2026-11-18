void swap_letters(char *word){
 char *letters = "CENITcenitPOLARpolar";
 char *swaps = "POLARpolarCENITcenit";
 int i, j;
 for(i = 0; word[i] != '\0'; i++){
  for(j = 0; letters[j] != '\0'; j++){
   if(word[i] == letters[j]){
    word[i] = swaps[j];
    break;
   }
  }
 }
}