char *get_test_name(int test)
{
  if (test == 128)
    return "sendpage";
  if (test == 129)
    return "sendmsg";
  return "unknown";
}