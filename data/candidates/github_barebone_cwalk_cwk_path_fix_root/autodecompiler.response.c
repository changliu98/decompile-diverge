void cwk_path_fix_root(char *buffer, size_t buffer_size,
  size_t length)
{
  size_t i;




  if (path_style == 0) {
    if (length > buffer_size) {
      length = buffer_size;
    }

    for (i = 0; i < length; ++i) {
      if (cwk_path_is_separator(buffer + i) & 1) {

        buffer[i] = separators[0];
      }
    }
  } else {
# 1000 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/realtsiry/rockbox4linux/refs/heads/master/apps/plugins/cwKpath.c"
  }
}