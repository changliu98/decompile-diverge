static void func0(unsigned int v, char bf[4])
{
    if (v < 0x80) {
        bf[0] = v;
        bf[1] = '\0';
    } else if (v < 0x800) {
        bf[0] = (v >> 6) | 0xC0;
        bf[1] = (v & 0x3F) | 0x80;
        bf[2] = '\0';
    } else if (v < 0x10000) {
        bf[0] = (v >> 12) | 0xE0;
        bf[1] = ((v >> 6) & 0x3F) | 0x80;
        bf[2] = (v & 0x3F) | 0x80;
        bf[3] = '\0';
    } else if (v < 0x200000) {
        bf[0] = (v >> 18) | 0xF0;
        bf[1] = ((v >> 12) & 0x3F) | 0x80;
        bf[2] = ((v >> 6) & 0x3F) | 0x80;
        bf[3] = (v & 0x3F) | 0x80;
        bf[4] = '\0';
    } else {
        bf[0] = '?';
        bf[1] = '\0';
    }
}