const char *cause_excode_text(int excode) {
    return cause_excode_text_txt[(excode & 0x7c) >> 2];
}