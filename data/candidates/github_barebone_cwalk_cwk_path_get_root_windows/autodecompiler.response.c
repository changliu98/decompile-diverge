static void cwk_path_get_root_windows(char *begin, size_t *length)
{
  char *c;
  bool is_device_path;


  c = begin;
  *length = 0;

  if (*c == '\0') {
    return;
  }


  if (cwk_path_is_separator(c)) {

    ++c;


    if (!cwk_path_is_separator(c)) {

      ++*length;
      return;
    }

    ++c;


    if (*c == '?' || *c == '.') {

      ++c;


      is_device_path = cwk_path_is_separator(c);
    } else {

      is_device_path = false;
    }


    if (is_device_path) {

      *length = 4;
    } else {

      c = cwk_path_find_next_stop(c);


      while (cwk_path_is_separator(c)) {
        ++c;
      }


      c = cwk_path_find_next_stop(c);


      if (cwk_path_is_separator(c)) {

        ++c;
      }


      *length = c - begin;
    }
  } else {

    ++c;


    if (*c == ':') {

      *length = 2;


      ++c;


      if (cwk_path_is_separator(c)) {

        *length = 3;
      }
    }
  }
}