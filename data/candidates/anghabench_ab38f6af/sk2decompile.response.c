static unsigned int ad7192_get_temp_scale(bool is_neg) {
  if (is_neg)
    return 5630;
  else
    return 2815;
}