void unpack_dxt(unsigned char mask, unsigned short color0, unsigned short color1, unsigned char *target)
{
    unsigned char r0 = (unsigned char)((color0 & 0x1f) << 3);
    unsigned char g0 = (unsigned char)((color0 & 0x7e0) >> 3);
    unsigned char b0 = (unsigned char)((color0 & 0xf800) >> 8);

    unsigned char r1 = (unsigned char)((color1 & 0x1f) << 3);
    unsigned char g1 = (unsigned char)((color1 & 0x7e0) >> 3);
    unsigned char b1 = (unsigned char)((color1 & 0xf800) >> 8);

    switch(mask)
    {
        case 0:
            target[0] = r0;
            target[1] = g0;
            target[2] = b0;
            break;

        case 1:
            target[0] = r1;
            target[1] = g1;
            target[2] = b1;
            break;

        case 2:
            if(color0 > color1)
            {
                target[0] = (unsigned char)((2 * r0 + r1) / 3);
                target[1] = (unsigned char)((2 * g0 + g1) / 3);
                target[2] = (unsigned char)((2 * b0 + b1) / 3);
            }
            else
            {
                target[0] = (unsigned char)((r0 + r1) / 2);
                target[1] = (unsigned char)((g0 + g1) / 2);
                target[2] = (unsigned char)((b0 + b1) / 2);
            }
            break;

        case 3:
            if(color0 > color1)
            {
                target[0] = (unsigned char)((r0 + 2 * r1) / 3);
                target[1] = (unsigned char)((g0 + 2 * g1) / 3);
                target[2] = (unsigned char)((b0 + 2 * b1) / 3);
            }
            else
            {
                target[0] = 0;
                target[1] = 0;
                target[2] = 0;
            }
            break;
    }
}