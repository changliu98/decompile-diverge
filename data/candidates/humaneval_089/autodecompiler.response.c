void func0(char *plaintext, char *ciphertext){
 int i;
 int temp;

 for(i=0; plaintext[i] != '\0'; i++){
  temp = ((plaintext[i] - 'a') + 4) % 26;
  ciphertext[i] = temp + 'a';
 }
 ciphertext[i] = '\0';

}