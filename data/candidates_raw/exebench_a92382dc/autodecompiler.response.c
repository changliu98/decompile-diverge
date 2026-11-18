int
XGetScanlinePad (
 Display *dpy,
 int depth,
 int format,
 unsigned int *pad_return,
 unsigned int *scanline_pad_return)
{
 register ScreenFormat *fmt;
 register int i;

 *pad_return = *scanline_pad_return = 0;
 return(0);
}