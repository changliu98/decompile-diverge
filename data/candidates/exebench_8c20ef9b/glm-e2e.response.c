void advance_spos(struct SPos *pos) {
    pos->field0 = (pos->field0 + 1) % 43;  // 0x2b
    pos->field1 = (pos->field1 + 1) % 47;  // 0x2f
    pos->field2 = (pos->field2 + 1) % 51;  // 0x33
    pos->field3 = (pos->field3 + 1) % 53;  // 0x35
    pos->field4 = (pos->field4 + 1) % 59;  // 0x3b
}