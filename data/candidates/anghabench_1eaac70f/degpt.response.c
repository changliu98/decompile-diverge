int unconv_uid(int uid)
{
  // Convert a user ID by applying a linear transformation.
  // If user_id is negative, return -1 to indicate an invalid ID.
  // Otherwise, scale and shift the user_id using log_split_mod and log_split_min.
  return uid < 0 ? -1 : uid * scale_factor + offset_value;
}