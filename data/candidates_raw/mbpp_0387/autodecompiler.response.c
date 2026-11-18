char * check(char *hex){

 int len = strlen(hex);
 char *res;

 if(hex[len-1] == '0' || hex[len-1] == '2' || hex[len-1] == '4' || hex[len-1] == '6' || hex[len-1] == '8' || hex[len-1] == 'A' || hex[len-1] == 'C' || hex[len-1] == 'E')
  res = "Even";
 else
  res = "Odd";

 return res;
}