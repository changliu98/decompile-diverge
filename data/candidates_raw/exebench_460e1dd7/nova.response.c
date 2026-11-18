static void func0(DWORD *d)
{
    DWORD t = ((*d)&0xff000000) >> 24;
    t += ((*d)&0x00ff0000) >> 8;
    t += ((*d)&0x0000ff00) << 8;
    t += ((*d)&0x000000ff) << 24;
    *d = t;
}