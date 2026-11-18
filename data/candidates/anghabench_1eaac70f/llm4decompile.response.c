int unconv_uid (int user_id) {
  return user_id < 0 ? -1 : user_id * log_split_mod + log_split_min;
}