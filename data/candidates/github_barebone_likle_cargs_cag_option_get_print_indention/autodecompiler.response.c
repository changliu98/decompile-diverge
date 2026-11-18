size_t cag_option_get_print_indention(struct option *options, size_t num_options)
{
 size_t max = 20;
 size_t i;

 for (i = 0; ; i++) {
  size_t len;
  struct option *opt;

  if (i >= num_options)
   break;

  len = 4;
  opt = &options[i];

  if (opt->name && *opt->name) {
   len += strlen(opt->name) * 4 - 2;
   if (opt->has_arg)
    len += strlen(opt->has_arg) + 4;
  } else if (opt->has_arg) {
   len += strlen(opt->has_arg) + 2;
  }

  if (opt->desc)
   len += strlen(opt->desc) + 1;

  if (len > max)
   max = len;
 }

 return max;
}