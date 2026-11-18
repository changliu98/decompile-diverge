int unconv_uid(int user_id)
{
  if (user_id < 0)
    return -1;
  return (log_split_min + (log_split_mod * user_id));
}