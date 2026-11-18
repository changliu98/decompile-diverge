static int
val_seg(int x)
{
 int n = 0;
 x >>= 7;
 if ((x & 0xf0) != 0) { x >>= 4; n += 4; }
 if ((x & 0x0c) != 0) { x >>= 2; n += 2; }
 if ((x & 0x02) != 0) { n += 1; }
 return n;
}