int __cdecl ImagingPcxDecode(Imaging im, ImagingCodecState state, UINT8 *buf, Py_ssize_t bytes)
{
  UINT8 v4; // dl
  UINT8 *buffer; // rax
  int x; // ecx
  UINT8 v7; // dl
  UINT8 *v8; // rax
  int v9; // ecx
  int v10; // eax
  int i; // [rsp+Ch] [rbp-44h]
  int stride; // [rsp+10h] [rbp-40h]
  int bands; // [rsp+14h] [rbp-3Ch]
  UINT8 *ptr; // [rsp+18h] [rbp-38h]
  UINT8 n; // [rsp+27h] [rbp-29h]

  if ( !strcmp(im->mode, "1") && state->xsize > 8 * state->bytes )
  {
    state->errcode = -1;
    return -1;
  }
  else
  {
    ptr = buf;
    while ( 1 )
    {
      if ( bytes < 1 )
        return (_DWORD)ptr - (_DWORD)buf;
      if ( (*ptr & 0xC0) == 192 )
      {
        if ( bytes < 2 )
          return (_DWORD)ptr - (_DWORD)buf;
        for ( n = *ptr & 0x3F; n; --n )
        {
          if ( state->x >= state->bytes )
          {
            state->errcode = -1;
            break;
          }
          v4 = ptr[1];
          buffer = state->buffer;
          x = state->x;
          state->x = x + 1;
          buffer[x] = v4;
        }
        ptr += 2;
        bytes -= 2LL;
      }
      else
      {
        v7 = *ptr;
        v8 = state->buffer;
        v9 = state->x;
        state->x = v9 + 1;
        v8[v9] = v7;
        ++ptr;
        --bytes;
      }
      if ( state->x >= state->bytes )
      {
        if ( state->bytes % state->xsize && state->bytes > state->xsize )
        {
          bands = state->bytes / state->xsize;
          stride = state->bytes / bands;
          for ( i = 1; i < bands; ++i )
            memmove(&state->buffer[state->xsize * i], &state->buffer[stride * i], state->xsize);
        }
        state->shuffle(
          (UINT8 *)&(&im->image[state->yoff])[state->y][im->pixelsize * state->xoff],
          state->buffer,
          state->xsize);
        state->x = 0;
        v10 = state->y + 1;
        state->y = v10;
        if ( v10 >= state->ysize )
          return -1;
      }
    }
  }
}