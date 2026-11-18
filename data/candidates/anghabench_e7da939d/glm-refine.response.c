const char *__cdecl test_to_str(int test)
{
  switch (test)
  {
    case 128:
      return "sendpage";
    case 129:
      return "sendmsg";
    default:
      return "unknown";
  }
}