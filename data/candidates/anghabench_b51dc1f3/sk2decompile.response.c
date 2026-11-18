int get_sorting_mode(int mode) {
  if (mode < 0 || mode >= 128)
    return -1;
  else
    return sorting_mode[mode];
}