size_t __cdecl cag_option_get_print_indention(const cag_option *options, size_t option_count)
{
  const cag_option *option; // [rsp+0h] [rbp-30h]
  size_t result; // [rsp+8h] [rbp-28h]
  size_t indention; // [rsp+10h] [rbp-20h]
  size_t option_index; // [rsp+18h] [rbp-18h]

  result = 20LL;
  for ( option_index = 0LL; option_index < option_count; ++option_index )
  {
    indention = 4LL;
    option = &options[option_index];
    if ( option->access_letters && *option->access_letters )
    {
      indention = 4 * strlen(option->access_letters) - 2 + 4;
      if ( option->access_name )
        indention += strlen(option->access_name) + 4;
    }
    else if ( option->access_name )
    {
      indention = strlen(option->access_name) + 6;
    }
    if ( option->value_name )
      indention += strlen(option->value_name) + 1;
    if ( indention > result )
      result = indention;
  }
  return result;
}