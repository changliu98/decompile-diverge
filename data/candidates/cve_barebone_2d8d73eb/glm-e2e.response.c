void EveAddVerdict(SCJbCtx *jb, Packet *p) {
    SCJbOpenObject(jb, str_2004);

    if (PacketCheckAction(p, 0x1c)) {
        if (EngineModeIsIPS() != 0) {
            SCJbSetFormatted(jb, str_200c);
        } else {
            SCJbSetFormatted(jb, str_201c);
        }

        if (PacketCheckAction(p, 0x4)) {
            SCJbSetFormatted(jb, str_202d);
        } else if (PacketCheckAction(p, 0x8)) {
            SCJbSetFormatted(jb, str_2049);
        } else if (PacketCheckAction(p, 0x10)) {
            SCJbSetFormatted(jb, str_2065);
        }

        SCJbOpenArray(jb, str_207c);
        
        uint8_t action = *(uint8_t *)p;
        if (action == 1 || action == 6 || action == 17 || action == 58) {
            SCJbAppendString(jb, str_2083);
        } else if (action == 6) { // Note: action == 6 is unreachable due to the previous condition
            SCJbAppendString(jb, str_208f);
        }

        SCJbClose(jb);
    } else {
        if (PacketCheckAction(p, 0x2) && EngineModeIsIPS() != 0) {
            SCJbSetFormatted(jb, str_200c);
        } else if (PacketCheckAction(p, 0x80)) {
            SCJbSetFormatted(jb, str_2099);
        } else {
            // Complex pointer arithmetic to extract a specific flag
            // p->some_ptr + (p->field_at_0x8 * 0x28) + 0x4
            uint8_t *ptr = (uint8_t *)p + 0x10;
            uint16_t offset = *(uint16_t *)((uint8_t *)p + 0x8);
            uint8_t val = *(ptr + (offset * 0x28) + 0x4);
            
            if ((val & 0x20) != 0) {
                SCJbSetFormatted(jb, str_20ab);
            } else {
                SCJbSetFormatted(jb, str_201c);
            }
        }
    }

    SCJbClose(jb);
}