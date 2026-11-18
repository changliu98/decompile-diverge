void __cdecl mobi_buffer_move(MOBIBuffer *buf, const int offset, const size_t len)
{
  unsigned __int8 *source; // [rsp+8h] [rbp-28h]
  unsigned __int8 *sourcea; // [rsp+8h] [rbp-28h]
  size_t aoffset; // [rsp+10h] [rbp-20h]

  aoffset = abs(offset);
  source = &buf->data[buf->offset];
  if ( offset < 0 )
  {
    if ( buf->offset < aoffset )
    {
      buf->error = MOBI_BUFFER_END;
      return;
    }
    sourcea = &source[-aoffset];
  }
  else
  {
    if ( len + aoffset + buf->offset > buf->maxlen )
    {
      buf->error = MOBI_BUFFER_END;
      return;
    }
    sourcea = &source[aoffset];
  }
  memmove(&buf->data[buf->offset], sourcea, len);
  buf->offset += len;
}