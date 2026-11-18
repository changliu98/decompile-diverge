static bool is_special_type(int type) {
  bool ret = true;
  if ((type & 0x0f) != TYPE_SPECIAL_FLOAT && (type & 0x0f) != TYPE_SPECIAL_INT)
    ret = false;
  return ret;
}