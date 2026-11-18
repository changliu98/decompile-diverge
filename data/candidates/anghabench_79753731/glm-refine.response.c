bool __cdecl check_attr_len(unsigned int attr_len, unsigned int expected_len)
{
  if (expected_len == attr_len)
    return true;

  if (expected_len == OVS_ATTR_NESTED)
    return true;

  return expected_len == OVS_ATTR_VARIABLE;
}