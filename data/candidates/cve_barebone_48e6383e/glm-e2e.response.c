int get_number(int colon, int *mouse_used) {
    int number = 0;
    int count = 0;
    int c;
    int ret;

    if (mouse_used != NULL) {
        *mouse_used = 0;
    }

    if (msg_silent != 0) {
        return 0;
    }

    no_mapping++;
    allow_keys++;

    while (1) {
        windgoto(msg_row, msg_col);
        c = safe_vgetc();

        if (c >= '0' && c <= '9') {
            number = number * 10 + c - '0';
            msg_putchar(c);
            count++;
            continue;
        }

        if (c == 0xffffbb95 || c == 0xffffaf03 || c == 0xffff9d95 || c == 0x8) {
            if (count > 0) {
                msg_puts("\b \b");
                count--;
            }
            number /= 10;
            continue;
        }

        if (mouse_used != NULL && c == 0xffffd303) {
            *mouse_used = 1;
            number = mouse_row + 1;
            break;
        }

        if (number == 0 && c == ':' && colon != 0) {
            stuffcharReadbuff(':');
            if (!exmode_active) {
                cmdline_row = msg_row;
            }
            skip_redraw = 1;
            do_redraw = 0;
            break;
        }

        if (c == 3 || c == 0x1b || c == 'q') {
            number = 0;
            break;
        }

        if (c == '\r' || c == '\n') {
            break;
        }
    }

    no_mapping--;
    allow_keys--;

    return number;
}