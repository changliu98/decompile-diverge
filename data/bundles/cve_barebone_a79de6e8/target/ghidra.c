void mobi_buffer_move(MOBIBuffer *buf,int offset,size_t len)

{
  int iVar1;
  ulong uVar2;
  uchar *source;
  size_t aoffset;
  size_t len_local;
  int offset_local;
  MOBIBuffer *buf_local;
  
  iVar1 = abs(offset);
  uVar2 = (ulong)iVar1;
  if (offset < 0) {
    if (buf->offset < uVar2) {
      buf->error = MOBI_BUFFER_END;
      return;
    }
    uVar2 = -uVar2;
  }
  else if (buf->maxlen < buf->offset + uVar2 + len) {
    buf->error = MOBI_BUFFER_END;
    return;
  }
  source = buf->data + uVar2 + buf->offset;
  memmove(buf->data + buf->offset,source,len);
  buf->offset = len + buf->offset;
  return;
}