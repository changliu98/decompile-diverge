const char *__cdecl cause_excode_text(int cause)
{
  return cause_excode_text_txt[(cause & 0x7C) >> 2];
}