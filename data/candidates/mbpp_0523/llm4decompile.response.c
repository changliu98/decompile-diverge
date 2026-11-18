char* func0(char* str1)
{
 int i=0,len=0,has_upper=0,has_lower=0,has_digit=0,is_valid=0;
 len=strlen(str1);
 for(i=0;i<len;i++)
 {
  if(str1[i]>='A' && str1[i]<='Z')
   has_upper=1;
  if(str1[i]>='a' && str1[i]<='z')
   has_lower=1;
  if(str1[i]>='0' && str1[i]<='9')
   has_digit=1;
 }
 func0::result[0]='\0';
 if(!has_upper)
  strcat(func0::result,"String must have 1 upper case character,");
 if(!has_lower)
  strcat(func0::result,"String must have 1 lower case character,");
 if(!has_digit)
  strcat(func0::result,"String must have 1 number,");
 if(len<8)
  strcat(func0::result,"String length should be atleast 8,");
 if(has_upper && has_lower && has_digit && len>=8)
  strcpy(func0::result,"Valid string.");
 else
 {
  i=strlen(func0::result)-1;
  if(func0::result[i]==',')
   func0::result[i]='\0';
 }
 return func0::result;
}