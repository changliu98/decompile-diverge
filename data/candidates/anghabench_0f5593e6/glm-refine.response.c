const char *cause_excode_text(int cause)
{
    int index = (cause >> 2) & 0x1F;
    return cause_excode_text_txt[index];
}