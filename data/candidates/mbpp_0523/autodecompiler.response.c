char* func0(char* inputstring)
{
 int hasUpper = 0;
 int hasLower = 0;
 int hasDigit = 0;
 int isValid = 1;
 int length = strlen(inputstring);
 int idx = 0;

 while(1)
 {
  if(idx < length)
  {
   if(isupper(inputstring[idx]))
   {
    hasUpper = 1;
   }
   if(islower(inputstring[idx]))
   {
    hasLower = 1;
   }
   if(isdigit(inputstring[idx]))
   {
    hasDigit = 1;
   }
  }
  else
  {
   break;
  }
  idx++;
 }

 func0_result[0] = '\0';

 if(!hasUpper)
 {
  strcat(func0_result, "String must have 1 upper case character,");
 }
 if(!hasLower)
 {
  strcat(func0_result, "String must have 1 lower case character,");
 }
 if(!hasDigit)
 {
  strcat(func0_result, "String must have 1 number,");
 }
 if(length < 9)
 {
  strcat(func0_result, "String length should be atleast 8,");
 }

 if(hasUpper && hasLower && hasDigit && length > 7)
 {
  strcpy(func0_result, "Valid string.");
 }
 else
 {
  int resultLen = strlen(func0_result);
  if(func0_result[resultLen-1] == ',')
  {
   func0_result[resultLen-1] = '\0';
  }
 }

 return func0_result;
}