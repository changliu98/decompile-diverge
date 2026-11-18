char* dec_to_bin(int a){
 char temp[6];
 sprintf(temp,"%d",a);
 int temp2=0;
 int i=0;
 while(1){
  if(temp[i]=='\0') break;
  temp2+=temp[i]-48;
  i++;
 }
 char* bin = malloc(sizeof(char)*33);
 int j=0;
 if(temp2==0) bin[j++]='0';
 while(temp2>0){
  bin[j++]=temp2%2+48;
  temp2/=2;
 }
 bin[j]='\0';
 int k=0;
 while(k<j/2){
  char swap=bin[k];
  bin[k]=bin[j-k-1];
  bin[j-k-1]=swap;
  k++;
 }
 return bin;
}