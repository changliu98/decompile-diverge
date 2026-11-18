int func0(char str[], char ch){
   int i;
   int count = 0;
   for (i = 0; i < strlen(str); i++)
      if (str[i] == ch)
         count++;
   return count;
}