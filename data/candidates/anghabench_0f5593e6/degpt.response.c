// Returns the human-readable error message corresponding to the given exception code.
// The 'cause' parameter is masked with 0x7c (binary 1111100) and shifted right by 2 bits
// to index into the 'txt' array, which contains the text descriptions for valid exception codes.
char * get_exception_message(int exception_code)
{
  return get_exception_message::exception_messages[(int)(exception_code & 0x7cU) >> 2];
}