int nsgif__deinterlace(unsigned int max, unsigned int *len, unsigned char *c)
{
    unsigned char done;
    unsigned int tmp;

    *len += *c & 0x0f;
    if (*len < max) {
        done = 1;
    } else {
        tmp = *c;
        switch (tmp) {
        case 0x08:
            *len = 4;
            *c = 8;
            if (*len < max) {
                done = 1;
            }
            break;
        case 0x04:
            *len = 2;
            *c = 4;
            if (*len < max) {
                done = 1;
            }
            break;
        case 0x02:
            *len = 1;
            *c = 2;
            if (*len < max) {
                done = 1;
            }
            break;
        default:
            done = 0;
        }
    }

    return done ? 1 : 0;
}