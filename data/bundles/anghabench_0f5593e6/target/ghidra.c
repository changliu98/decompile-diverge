char * cause_excode_text(int cause)

{
  int cause_local;
  
  return cause_excode_text::txt[(int)(cause & 0x7cU) >> 2];
}