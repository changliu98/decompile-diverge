int bracketed_paste(int mode, int drop, growarray *gap) {
    char buf[0x64];
    int idx = 0;
    char *tp = find_termcode("\x1b[201~");
    int ret = -1;
    int save_allow_keys = allow_keys;
    int save_p_paste = p_paste;

    if (tp != NULL && strlen(tp) < 0x41) {
        tp = NULL;
    }

    no_mapping++;
    allow_keys = 0;
    if (p_paste == 0) {
        set_option_value("paste", 1, NULL, 0);
    }

    while (1) {
        if (tp == NULL && vpeekc() == 0) {
            break;
        }

        int c;
        while (1) {
            c = vgetc();
            if (c == 0x1001 || c == 0x1002 || c == 0x1003) {
                continue;
            }
            break;
        }

        if (c == 0 || got_int != 0 || (ex_normal_busy > 0 && c == 3)) {
            break;
        }

        if (has_mbyte) {
            idx += mb_char2bytes(c, buf + idx);
        } else {
            buf[idx++] = (char)c;
        }
        buf[idx] = '\0';

        if (tp != NULL && strncmp(buf, tp, idx) == 0) {
            if (tp[idx] == '\0') {
                break;
            }
            continue;
        }

        if (drop != 0) {
            idx = 0;
            continue;
        }

        switch (mode) {
            case 1:
                put_on_cmdline(buf, idx, 1);
                break;
            case 2:
                if (gap != NULL && ga_grow(gap, idx) == 1) {
                    memmove(gap->ga_data + gap->ga_len, buf, idx);
                    gap->ga_len += idx;
                }
                break;
            case 3:
                if (stop_arrow() == 1) {
                    c = buf[0];
                    if (idx == 1 && (c == 0xd || c == 0x1004 || c == 0xa)) {
                        ins_eol(c);
                    } else {
                        ins_char_bytes(buf, idx);
                        AppendToRedobuffLit(buf, idx);
                    }
                }
                break;
            default:
                if (ret == -1) {
                    if (has_mbyte) {
                        ret = mb_ptr2char(buf);
                    } else {
                        ret = buf[0];
                    }
                }
                break;
        }
        idx = 0;
    }

    no_mapping--;
    allow_keys = save_allow_keys;
    if (save_p_paste == 0) {
        set_option_value("paste", 0, NULL, 0);
    }

    return ret;
}