int ImagingPcxDecode(Imaging im,ImagingCodecState state,UINT8 *buf,Py_ssize_t bytes)

{
  UINT8 UVar1;
  int iVar2;
  int iVar3;
  int i;
  int stride;
  int bands;
  UINT8 *ptr;
  UINT8 n;
  Py_ssize_t bytes_local;
  UINT8 *buf_local;
  ImagingCodecState state_local;
  Imaging im_local;
  
  iVar2 = strcmp(im->mode,"1");
  ptr = buf;
  bytes_local = bytes;
  if ((iVar2 == 0) && (state->bytes * 8 < state->xsize)) {
    state->errcode = -1;
  }
  else {
    do {
      do {
        if (bytes_local < 1) {
          return (int)ptr - (int)buf;
        }
        if ((*ptr & 0xc0) == 0xc0) {
          if (bytes_local < 2) {
            return (int)ptr - (int)buf;
          }
          for (n = *ptr & 0x3f; n != '\0'; n = n + 0xff) {
            if (state->bytes <= state->x) {
              state->errcode = -1;
              break;
            }
            UVar1 = ptr[1];
            iVar2 = state->x;
            state->x = iVar2 + 1;
            state->buffer[iVar2] = UVar1;
          }
          ptr = ptr + 2;
          bytes_local = bytes_local + -2;
        }
        else {
          UVar1 = *ptr;
          iVar2 = state->x;
          state->x = iVar2 + 1;
          state->buffer[iVar2] = UVar1;
          ptr = ptr + 1;
          bytes_local = bytes_local + -1;
        }
      } while (state->x < state->bytes);
      if ((state->bytes % state->xsize != 0) && (state->xsize < state->bytes)) {
        iVar3 = state->bytes / state->xsize;
        iVar2 = state->bytes;
        for (i = 1; i < iVar3; i = i + 1) {
          memmove(state->buffer + i * state->xsize,state->buffer + i * (iVar2 / iVar3),
                  (long)state->xsize);
        }
      }
      (*state->shuffle)((UINT8 *)(im->image[state->y + state->yoff] + state->xoff * im->pixelsize),
                        state->buffer,state->xsize);
      state->x = 0;
      iVar2 = state->y + 1;
      state->y = iVar2;
    } while (iVar2 < state->ysize);
  }
  return -1;
}