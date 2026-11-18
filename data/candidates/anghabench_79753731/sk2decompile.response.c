static bool check_attr_len(int len, int attr_len) {
  if (len == attr_len) return true;
  if (attr_len == ATTR_LEN_UNLIMITED) return true;
  if (attr_len == ATTR_LEN_UNKNOWN) return true;
  return false;
}