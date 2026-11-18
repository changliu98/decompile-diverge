Py_ssize_t
ImagingPcxDecode(Imaging im, ImagingCodecState state,
  unsigned char *buf, Py_ssize_t bytes)
{
    unsigned char *p;
    unsigned char *obuf;
    Py_ssize_t obytes;
    int stride;
    int bands;


    if (!strcmp(im->mode, "1") && state->xsize > state->bytes * 8) {
 state->errcode = -1;
 return -1;
    }


    p = buf;
    obuf = buf;
    obytes = bytes;
    while (obytes > 0) {
 if ((*p & 0xc0) == 0xc0) {
     int count;
     if (obytes < 2)
  break;
     count = *p++ & 0x3f;
     while (count--) {
  if (state->x >= state->bytes) {
      state->errcode = -1;
      break;
  }
  state->buffer[state->x++] = *p;
     }
     p++;
     obytes -= 2;
 } else {
     state->buffer[state->x++] = *p++;
     obytes--;
 }
 if (state->x >= state->bytes) {

     if (state->bytes % state->xsize && state->bytes > state->xsize) {
  int i;
  stride = state->bytes / state->xsize;
  for (i=1; i<stride; i++)
      memmove(state->buffer+i*state->xsize,
       state->buffer+i*stride, state->xsize);
     }
     state->shuffle((unsigned char*)(im->image[state->y+state->yoff]+state->xoff*im->pixelsize), state->buffer, state->xsize);
     state->x = 0;
     state->y++;
     if (state->y >= state->ysize)
  break;
 }
    }
    return p - obuf;
}