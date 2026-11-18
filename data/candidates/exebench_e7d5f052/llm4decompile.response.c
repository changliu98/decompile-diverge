void SJIStoJIS (int *p1, int *p2)
{
 register unsigned char c1 = (unsigned char) (*p1);
 register unsigned char c2 = (unsigned char) (*p2);
 register int adjust = c1 < 160 ? 112 : 176;
 register int rowOffset = c2 < 159 ? 112 : 176;
 register int cellOffset = adjust / 2;

 if (c2 >= 159) {
  cellOffset++;
 }

 *p1 = ((c1 - adjust) << 1) - cellOffset;
 *p2 -= rowOffset;
}