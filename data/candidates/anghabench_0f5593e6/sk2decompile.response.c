const char* cause_excode_text(unsigned int cause) {
  static const char* excode_text[] = {"OK", "EXC_BAD_ACCESS", "EXC_BAD_ACCESS",
                                      "EXC_BAD_ACCESS", "EXC_BAD_ACCESS",
                                      "EXC_UNKNOWN"};
  return excode_text[(cause & 0x7c) >> 2];
}