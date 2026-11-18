char *func0(char *main_string,char *sub_string)
{
 char new_sub_string[100];
 regex_t reg;
 int match;
 char *output;

 if(strstr(main_string,sub_string))
 {
  memset(new_sub_string,0,sizeof(new_sub_string));
  new_sub_string[0] = '^';
  strcat(new_sub_string,sub_string);

  regcomp(&reg,new_sub_string,0);
  match = regexec(&reg,main_string,0,NULL,0);
  regfree(&reg);

  if(!match)
   output = "string starts with the given substring";
  else
   output = "string doesnt start with the given substring";
 }
 else
  output = "entered string isnt a substring";

 return output;
}