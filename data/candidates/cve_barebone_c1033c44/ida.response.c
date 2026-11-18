void *__cdecl mrb_realloc(mrb_state *mrb, void *p, size_t len)
{
  void *p2; // [rsp+8h] [rbp-28h]

  p2 = mrb_realloc_simple(mrb, p, len);
  if ( !len )
    return p2;
  if ( p2 )
  {
    *((_BYTE *)&mrb->gc + 96) &= ~0x10u;
  }
  else
  {
    mrb_free(mrb, p);
    *((_BYTE *)&mrb->gc + 96) = *((_BYTE *)&mrb->gc + 96) & 0xEF | 0x10;
    mrb_raise_nomemory(mrb);
  }
  return p2;
}