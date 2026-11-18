int __cdecl rom_copy(uint8_t *dest, hwaddr addr, size_t size)
{
  Rom *rom; // [rsp+0h] [rbp-40h]
  hwaddr l; // [rsp+8h] [rbp-38h]
  uint8_t *d; // [rsp+10h] [rbp-30h]
  hwaddr end; // [rsp+20h] [rbp-20h]

  end = size + addr;
  LODWORD(d) = (_DWORD)dest;
  LODWORD(l) = 0;
  for ( rom = (Rom *)roms; rom; rom = rom->next.tqe_next )
  {
    if ( !rom->fw_file && !rom->mr && rom->romsize + rom->addr >= addr )
    {
      if ( rom->addr > end )
        return l + (_DWORD)d - (_DWORD)dest;
      d = &dest[rom->addr - addr];
      l = rom->datasize;
      if ( &d[l] > &dest[size] )
        l = addr - rom->addr;
      if ( l )
        memcpy(d, rom->data, l);
      if ( rom->romsize > rom->datasize )
      {
        d += l;
        l = rom->romsize - rom->datasize;
        if ( &d[l] > &dest[size] )
          l = dest - d;
        if ( l )
          memset(d, 0, l);
      }
    }
  }
  return l + (_DWORD)d - (_DWORD)dest;
}