bool check_attr_len(uint attr_len,uint expected_len)

{
  undefined1 local_11;
  uint expected_len_local;
  uint attr_len_local;
  
  local_11 = true;
  if ((expected_len != attr_len) && (local_11 = true, expected_len != OVS_ATTR_NESTED)) {
    local_11 = expected_len == OVS_ATTR_VARIABLE;
  }
  return (bool)local_11;
}