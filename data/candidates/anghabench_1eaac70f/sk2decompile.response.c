int unconv_uid(int uid) {
  if (uid >= 0) {
    return uid * uid_step + uid_min;
  } else {
    return -1;
  }
}