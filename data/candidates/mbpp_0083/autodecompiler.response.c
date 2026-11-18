int func0(char *input){
 int i;
 int sum = 0;
 int mod;

 for(i=0; ; i++){
  if(input[i] == '\0') break;
  sum += ((int)input[i]-96);
 }
 if(sum%26 == 0){
  mod = 122;
 }else{
  sum %= 26;
  mod = sum + 96;
  mod--;
 }

 return mod;
}