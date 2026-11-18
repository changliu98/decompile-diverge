bool __cdecl check_attr_len(unsigned int attr_len, unsigned int expected_len)
{
  bool v3; // [rsp+1h] [rbp-9h]

  v3 = 1;
  if ( expected_len != attr_len )
  {
    v3 = 1;
    if ( expected_len != OVS_ATTR_NESTED )
      return expected_len == OVS_ATTR_VARIABLE;
  }
  return v3;
}