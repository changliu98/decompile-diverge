static int
ImagingPcxDecode( mpg123_handle_t *fr, audio_buffer_t *b, unsigned char *buffer, long len )
{
 int ret;
 unsigned char *bufpos = buffer;

 if( strcmp( fr->name, "1" ) == 0 && b->rdata.size > b->rawbuffsiz * 8 )
 {

  b->fullend = -1;
  ret = -1;
 }
 else
 {
  do
  {
   if( len < 2 )
   {
    ret = bufpos - buffer;
    break;
   }

   if( (*bufpos & 0xc0) == 0xc0 )
   {

    if( len < 3 )
    {
     ret = bufpos - buffer;
     break;
    }

    unsigned char skip = *bufpos & 0x3f;
    while( skip > 0 )
    {
     if( b->rdata.fill >= b->rawbuffsiz )
     {
      b->fullend = -1;
      break;
     }
     b->rdata.buffer[b->rdata.fill++] = *(bufpos + 1);
     skip--;
    }
    bufpos += 2;
    len -= 2;
   }
   else
   {
    b->rdata.buffer[b->rdata.fill++] = *bufpos;
    bufpos++;
    len--;
   }

   if( b->rdata.fill >= b->rawbuffsiz )
   {
    if( b->rawbuffsiz % b->rdata.size != 0 && b->rawbuffsiz > b->rdata.size )
    {
     int i;
     int bands = b->rawbuffsiz / b->rdata.size;
     int stride = b->rawbuffsiz / bands;
     for( i = 1; i < bands; i++ )
     {
      memmove( b->rdata.buffer + i * b->rdata.size,
       b->rdata.buffer + i * stride,
       b->rdata.size );
     }
    }

    fr->wrappercallback( fr->wrapperdata[ b->index + b->wraps ], b->rdata.buffer, b->rdata.size, b->wraps * fr->af.encsize );
    b->rdata.fill = 0;
    b->wraps++;
    if( b->wraps >= b->wrappercount )
    {
     ret = -1;
     break;
    }
   }
  } while( 1 );
 }

 return ret;
}