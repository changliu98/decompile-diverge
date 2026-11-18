char *func0(char *input){
 char vowels[11] = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u', '\0'};
 int accepted[10];
 int i, j, flag, counter;
 char *message;

 for(i=0; i<10; i++){
  accepted[i] = 0;
 }
 counter = 0;
 for(i=0; input[i] != '\0'; i++){
  flag = 0;
  for(j=0; j<11; j++){
   if(input[i] == vowels[j]){
    flag = 1;
    break;
   }
  }
  if(flag){
   if(accepted[j] == 0){
    accepted[j] = 1;
    counter++;
   }
  }
 }

 if(counter >= 5){
  message = "accepted";
 }else{
  message = "not accepted";
 }

 return message;
}