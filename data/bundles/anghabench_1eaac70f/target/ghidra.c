int unconv_uid(int user_id)

{
  int user_id_local;
  undefined4 local_c;
  
  if (user_id < 0) {
    local_c = -1;
  }
  else {
    local_c = user_id * log_split_mod + log_split_min;
  }
  return local_c;
}