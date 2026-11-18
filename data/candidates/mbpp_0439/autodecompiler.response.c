int func0(int arr[], int len){
 char str[256];
 memset(str, 0, sizeof(str));
 char temp[32];
 int i = 0;
 while(1){
  if(i >= len) break;
  sprintf(temp, "%d", arr[i]);
  strcat(str, temp);
  i++;
 }
 return atoi(str);
}