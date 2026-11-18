void OPL2_ChannelUpdateRhythm(struct Bitmap *self, unsigned char state) {
    self->state = state;
    struct Square *current;
    struct Square *next;
    struct Square *previous;
    unsigned char i;
    while (1) {
        if (self->state & 0x20) {
            current = &self->squares[0];
            next = &self->squares[1];
            previous = &self->squares[2];
        } else {
            current = &self->squares[2];
            next = &self->squares[1];
            previous = &self->squares[0];
        }
        for (i = 6; i < 10; i++) {
            if (i < 9) {
                current->state = 1;
            } else {
                current->state = 0;
            }
            current = next;
            next = previous;
            previous = current;
        }
        if (self->state & 0x01) {
            Set(current, 2);
        } else {
            Reset(current, 2);
        }
        if (self->state & 0x02) {
            Set(next, 2);
        } else {
            Reset(next, 2);
        }
        if (self->state & 0x04) {
            Set(previous, 2);
        } else {
            Reset(previous, 2);
        }
        if (self->state & 0x08) {
            Set(current, 2);
        } else {
            Reset(current, 2);
        }
        if (self->state & 0x10) {
            Set(next, 2);
        } else {
            Reset(next, 2);
        }
    }
}