int unconv_uid (int user_id) {
  int t;
  if (user_id >= 0) {
    t = log_split_min + user_id * log_split_mod;
  } else {
    t = -1;
  }
  return t;
}