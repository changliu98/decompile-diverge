char *cause_excode_text(int excode)
{
  int cause = excode & 0x7c;
  return cause_excode_text_txt[cause>>2];
}