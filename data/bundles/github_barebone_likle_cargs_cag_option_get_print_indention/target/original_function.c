static size_t cag_option_get_print_indention(const cag_option *options,
  size_t option_count)
{
  size_t option_index, indention, result;
  const cag_option *option;

  result = CAG_OPTION_PRINT_MIN_INDENTION;

  for (option_index = 0; option_index < option_count; ++option_index) {
    indention = CAG_OPTION_PRINT_DISTANCE;
    option = &options[option_index];
    if (option->access_letters != NULL && *option->access_letters) {
      indention += strlen(option->access_letters) * 4 - 2;
      if (option->access_name != NULL) {
        indention += strlen(option->access_name) + 4;
      }
    } else if (option->access_name != NULL) {
      indention += strlen(option->access_name) + 2;
    }

    if (option->value_name != NULL) {
      indention += strlen(option->value_name) + 1;
    }

    if (indention > result) {
      result = indention;
    }
  }

  return result;
}