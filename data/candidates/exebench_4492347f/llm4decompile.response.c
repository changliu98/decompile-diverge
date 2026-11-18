int RGB565toI420(unsigned char *dest_ptr, int dest_width, int dest_height, int dest_pitch, int dest_x, int dest_y, int dest_dx, int dest_dy, unsigned char *src_ptr, int src_width, int src_height, int src_pitch, int src_x, int src_y, int src_dx, int src_dy)
{







    int x, y;
    unsigned char *p;
    unsigned char *q;
    unsigned char *r;
    unsigned char *s;
    unsigned char *t;
    unsigned char *u;
    int rgb;
    int r;
    int g;
    int b;
    int y0;
    int u0;
    int v0;
    int y1;
    int u1;
    int v1;
    int y2;
    int u2;
    int v2;
    int y3;
    int u3;
    int v3;

    p = dest_ptr;
    q = p + dest_pitch;
    r = q + dest_pitch / 2;
    s = p + dest_pitch * dest_height;
    t = s + dest_pitch / 2;
    u = src_ptr + src_pitch * src_y + src_x * 2;

    for (y = dest_height; y > 0; y -= 2) {
        for (x = dest_width; x > 0; x -= 2) {
            rgb = *((unsigned short *)u);
            r = (rgb >> 11) & 0x1f;
            g = (rgb >> 5) & 0x3f;
            b = (rgb) & 0x1f;
            rgb = *((unsigned short *)(u + 2));
            r += (rgb >> 11) & 0x1f;
            g += (rgb >> 5) & 0x3f;
            b += (rgb) & 0x1f;
            rgb = *((unsigned short *)(u + src_pitch));
            r += (rgb >> 11) & 0x1f;
            g += (rgb >> 5) & 0x3f;
            b += (rgb) & 0x1f;
            rgb = *((unsigned short *)(u + src_pitch + 2));
            r += (rgb >> 11) & 0x1f;
            g += (rgb >> 5) & 0x3f;
            b += (rgb) & 0x1f;
            r = (r * 2 + 4) / 9;
            g = (g * 2 + 4) / 9;
            b = (b * 2 + 4) / 9;
            y0 = (77 * r + 150 * g + 29 * b + 128) >> 8;
            u0 = (-43 * r - 85 * g + 128 * b + 128) >> 8;
            v0 = (128 * r - 107 * g - 21 * b + 128) >> 8;
            y1 = (77 * r + 150 * g + 29 * b + 128) >> 8;
            u1 = (-43 * r - 85 * g + 128 * b + 128) >> 8;
            v1 = (128 * r - 107 * g - 21 * b + 128) >> 8;
            y2 = (77 * r + 150 * g + 29 * b + 128) >> 8;
            u2 = (-43 * r - 85 * g + 128 * b + 128) >> 8;
            v2 = (128 * r - 107 * g - 21 * b + 128) >> 8;
            y3 = (77 * r + 150 * g + 29 * b + 128) >> 8;
            u3 = (-43 * r - 85 * g + 128 * b + 128) >> 8;
            v3 = (128 * r - 107 * g - 21 * b + 128) >> 8;
            *p++ = y0;
            *q++ = y1;
            *r++ = u0;
            *s++ = y2;
            *t++ = v0;
            *p++ = y3;
            *q++ = y3;
            *r++ = v1;
            *s++ = y3;
            *t++ = v2;
            u += 2 * 2;
        }
        p += dest_pitch * 2;
        q += dest_pitch * 2;
        r += dest_pitch / 2;
        s += dest_pitch * 2;
        t += dest_pitch / 2;
        u += src_pitch * 2;
    }

    return -1;
}