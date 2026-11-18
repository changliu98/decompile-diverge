static int iwgif_read_image(struct context *c) {
    int ret = 0;
    for (;;) {
        if (read_byte(c, &c->c, 1)!= 0) {
            c->c.op = read_byte(c, &c->c);
            c->c.op2 = read_byte(c, &c->c);
            c->c.op3 = read_byte(c, &c->c);
            c->c.op4 = read_byte(c, &c->c);
            c->c.op5 = (c->c.op5 & 0x40) >> 6;
            int op6 = (c->c.op5 & 0x80) >> 7;
            if (op6) {
                c->c.op6 = (1 << ((c->c.op5 & 0x7) + 1));
            }
            if (op6 && read_byte(c, &c->c, 1)!= 0) {
                continue;
            }
            if (c->c.op < 2 || c->c.op > 11) {
                error(&c->c, "invalid opcode %d", c->c.op);
            }
            if (c->c.op == 0) {
                break;
            }
            if (c->c.op == 1) {
                ret = 1;
                break;
            }
            if (c->c.op == 2) {
                if (c->c.op4 < c->c.op3) {
                    break;
                }
            }
            if (c->c.op == 3) {
                if (c->c.op4 < c->c.op3) {
                    break;
                }
            }
            if (c->c.op == 4) {
                if (c->c.op4 < c->c.op3) {
                    break;
                }
            }
            if (c->c.op == 5) {