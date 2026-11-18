void murcielagoCrypt(char *word){
 int i, j;
 char *letters = "MURCIELAGOmurcielago";
 char *numbers = "01234567890123456789";

 for(i=0; word[i] != '\0'; i++){
  for(j=0; letters[j] != '\0'; j++){
   if(word[i] == letters[j]){
    word[i] = numbers[j];
    break;
   }
  }
 }
}