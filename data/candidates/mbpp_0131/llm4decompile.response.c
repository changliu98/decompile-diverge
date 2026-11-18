char* func0(char* input_string)
{
 int index = 0, vowel_index = 0;
 char vowels[100];
 memset(vowels, 0, 100);

 for (index = 0; input_string[index] != '\0'; index++)
 {
  if (strchr("aeiouAEIOU", input_string[index]) != NULL)
  {
   vowels[vowel_index++] = input_string[index];
  }
 }
 vowels[vowel_index] = '\0';

 vowel_index = strlen(vowels) - 1;
 for (index = 0; input_string[index] != '\0'; index++)
 {
  if (strchr("aeiouAEIOU", input_string[index]) != NULL)
  {
   func0::result_string[index] = vowels[vowel_index--];
  }
  else
  {
   func0::result_string[index] = input_string[index];
  }
 }
 func0::result_string[index] = '\0';

 return func0::result_string;
}