int RGB32toRGB555(unsigned char *dest_ptr, int dest_width, int dest_height, int dest_pitch, int dest_x, int dest_y, int dest_dx, int dest_dy, unsigned char *src_ptr, int src_width, int src_height, int src_pitch, int src_x, int src_y, int src_dx, int src_dy)
{







    int x, y;
    int sr, sg, sb;
    int dr, dg, db;
    int r, g, b;
    int s_x, s_y, d_x, d_y;
    int s_pitch, d_pitch;
    unsigned char *s_ptr, *d_ptr;

    s_x = src_x;
    s_y = src_y;
    s_pitch = src_pitch;
    d_x = dest_x;
    d_y = dest_y;
    d_pitch = dest_pitch;
    s_ptr = src_ptr;
    d_ptr = dest_ptr;

    for (y = 0; y < dest_height; y++)
    {
        for (x = 0; x < dest_width; x++)
        {
            sr = ((int) ((*(s_ptr + (s_x + x) * 4 + 2))) << 24) & 0xFF000000;
            sg = ((int) ((*(s_ptr + (s_x + x) * 4 + 1))) << 16) & 0x00FF0000;
            sb = ((int) ((*(s_ptr + (s_x + x) * 4))) << 8) & 0x0000FF00;
            r = (sr >> 19) & 0x1F;
            g = (sg >> 11) & 0x1F;
            b = (sb >> 3) & 0x1F;
            dr = r << 10;
            dg = g << 5;
            db = b;
            *((unsigned short*)(d_ptr + (d_x + x) * 2)) = (unsigned short)(dr | dg | db);
        }
        s_ptr += s_pitch;
        d_ptr += d_pitch;
    }

    return 0;

}