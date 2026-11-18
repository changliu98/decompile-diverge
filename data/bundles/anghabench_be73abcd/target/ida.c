int __cdecl val_seg(int val)
{
  int r; // [rsp+0h] [rbp-8h]
  int vala; // [rsp+4h] [rbp-4h]

  r = 0;
  vala = val >> 7;
  if ( ((val >> 7) & 0xF0) != 0 )
  {
    vala = val >> 11;
    r = 4;
  }
  if ( (vala & 0xC) != 0 )
  {
    vala >>= 2;
    r += 2;
  }
  if ( (vala & 2) != 0 )
    ++r;
  return r;
}