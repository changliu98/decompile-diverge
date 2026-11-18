static void func0(unsigned char *a, unsigned char *b)
{
    int x = *a;
    int y = *b;
    int x1 = (x < 0x20)? 0x70 : 0x20;
    int y1 = (x % 2)? 0x1f : 0x20;
    int x2 = (y < 0x20)? 0x70 : 0x20;
    int y2 = (y % 2)? 0x1f : 0x20;

    *a = x + (x1 + y1) / 2;
    *b = y + (x2 + y2) / 2;
}