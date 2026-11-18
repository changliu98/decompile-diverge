char* func0(char* N)
{
 int len = strlen(N);
 char* str;
 if(N[len-1]=='0' || N[len-1]=='2' || N[len-1]=='4' || N[len-1]=='6' || N[len-1]=='8' || N[len-1]=='A' || N[len-1]=='C' || N[len-1]=='E')
  str = "Even";
 else
  str = "Odd";
 return str;
}