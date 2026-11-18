size_t cag_option_get_print_indention(const cag_option *options, size_t option_count)
{
 size_t result = 20;
 size_t option_index = 0;
 size_t indention = 0;

 for (option_index = 0; option_index < option_count; option_index++)
 {
  indention = 4;

  if (options[option_index].access_letters != NULL && options[option_index].access_letters[0] != '\0')
  {
   indention += strlen(options[option_index].access_letters) * 4 + 2;

   if (options[option_index].access_name != NULL)
   {
    indention += strlen(options[option_index].access_name) + 4;
   }
  }
  else if (options[option_index].access_name != NULL)
  {
   indention += strlen(options[option_index].access_name) + 6;
  }

  if (options[option_index].value_name != NULL)
  {
   indention += strlen(options[option_index].value_name) + 1;
  }

  if (indention > result)
  {
   result = indention;
  }
 }

 return result;
}