char * test_to_str(int test)

{
  int test_local;
  char *local_10;
  
  if (test == 0x80) {
    local_10 = "sendpage";
  }
  else if (test == 0x81) {
    local_10 = "sendmsg";
  }
  else {
    local_10 = "unknown";
  }
  return local_10;
}