size_t cag_option_get_print_indention(cag_option *options,size_t option_count)

{
  size_t sVar1;
  cag_option *option;
  size_t result;
  size_t indention;
  size_t option_index;
  size_t option_count_local;
  cag_option *options_local;
  
  result = 0x14;
  for (option_index = 0; option_index < option_count; option_index = option_index + 1) {
    indention = 4;
    if ((options[option_index].access_letters == (char *)0x0) ||
       (*options[option_index].access_letters == '\0')) {
      if (options[option_index].access_name != (char *)0x0) {
        sVar1 = strlen(options[option_index].access_name);
        indention = sVar1 + 6;
      }
    }
    else {
      sVar1 = strlen(options[option_index].access_letters);
      indention = sVar1 * 4 + 2;
      if (options[option_index].access_name != (char *)0x0) {
        sVar1 = strlen(options[option_index].access_name);
        indention = sVar1 + 4 + indention;
      }
    }
    if (options[option_index].value_name != (char *)0x0) {
      sVar1 = strlen(options[option_index].value_name);
      indention = sVar1 + 1 + indention;
    }
    if (result < indention) {
      result = indention;
    }
  }
  return result;
}