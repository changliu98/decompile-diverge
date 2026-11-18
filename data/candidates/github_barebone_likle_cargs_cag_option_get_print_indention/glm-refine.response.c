size_t __cdecl cag_option_get_print_indention(const cag_option *options, size_t option_count)
{
  const cag_option *option;
  size_t max_indention = 20;
  size_t current_indention;
  size_t option_index;

  for (option_index = 0; option_index < option_count; ++option_index)
  {
    current_indention = 4;
    option = &options[option_index];

    if (option->access_letters && *option->access_letters)
    {
      // 4 chars per access letter, plus 2 for the prefix/suffix formatting
      current_indention += 4 * strlen(option->access_letters) + 2;
      
      if (option->access_name)
        current_indention += strlen(option->access_name) + 4;
    }
    else if (option->access_name)
    {
      current_indention += strlen(option->access_name) + 2;
    }

    if (option->value_name)
      current_indention += strlen(option->value_name) + 1;

    if (current_indention > max_indention)
      max_indention = current_indention;
  }
  
  return max_indention;
}