char *__cdecl test_to_str(int test)
{
  if ( test == 128 )
    return "sendpage";
  if ( test == 129 )
    return "sendmsg";
  return "unknown";
}