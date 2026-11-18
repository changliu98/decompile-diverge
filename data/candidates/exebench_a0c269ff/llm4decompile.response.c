void swap_float_4(float *f)
{
    union float_4_byte_4 u;
    u.f = *f;
    u.b[0] = u.b[0] ^ u.b[3];
    u.b[3] = u.b[0] ^ u.b[3];
    u.b[0] = u.b[0] ^ u.b[3];
    u.b[1] = u.b[1] ^ u.b[2];
    u.b[2] = u.b[1] ^ u.b[2];
    u.b[1] = u.b[1] ^ u.b[2];
    *f = u.f;
}