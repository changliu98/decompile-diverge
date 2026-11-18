static const char *test_to_str(test_t test) {
  switch (test) {
    case TEST_SENDMSG:
      return "sendmsg";
    case TEST_SENDPAGE:
      return "sendpage";
    default:
      return "unknown";
  }
}