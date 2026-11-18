int __cdecl NeXTDecode(TIFF *tif, uint8 *buf, tmsize_t occ, uint16 s)
{
  __int64 v4; // rax
  unsigned __int8 *v5; // rax
  unsigned __int8 *v6; // rax
  __int64 v7; // rcx
  char v8; // al
  unsigned __int8 *v9; // rax
  unsigned __int8 *v10; // rax
  bool v12; // [rsp+17h] [rbp-79h]
  bool v13; // [rsp+23h] [rbp-6Dh]
  uint32 imagewidth; // [rsp+24h] [rbp-6Ch]
  char grey; // [rsp+28h] [rbp-68h]
  uint32 npixels; // [rsp+2Ch] [rbp-64h]
  tmsize_t off; // [rsp+30h] [rbp-60h]
  tmsize_t n; // [rsp+38h] [rbp-58h]
  tmsize_t na; // [rsp+38h] [rbp-58h]
  tmsize_t nb; // [rsp+38h] [rbp-58h]
  tmsize_t scanline; // [rsp+40h] [rbp-50h]
  uint8 *row; // [rsp+48h] [rbp-48h]
  tmsize_t cc; // [rsp+50h] [rbp-40h]
  __int64 cca; // [rsp+50h] [rbp-40h]
  unsigned __int8 *op; // [rsp+58h] [rbp-38h]
  unsigned __int8 *opa; // [rsp+58h] [rbp-38h]
  unsigned __int8 *bp_0; // [rsp+60h] [rbp-30h]
  tmsize_t occa; // [rsp+70h] [rbp-20h]

  occa = occ;
  op = buf;
  cc = occ;
  while ( 1 )
  {
    v4 = cc--;
    if ( v4 <= 0 )
      break;
    v5 = op++;
    *v5 = -1;
  }
  bp_0 = tif->tif_rawcp;
  cca = tif->tif_rawcc;
  scanline = tif->tif_scanlinesize;
  if ( !(occ % scanline) )
  {
    for ( row = buf; ; row += scanline )
    {
      v13 = 0;
      if ( cca > 0 )
        v13 = occa > 0;
      if ( !v13 )
      {
        tif->tif_rawcp = bp_0;
        tif->tif_rawcc = cca;
        return 1;
      }
      v6 = bp_0++;
      n = *v6;
      --cca;
      if ( *v6 )
      {
        if ( n == 64 )
        {
          if ( cca < 4
            || (off = bp_0[1] + (*bp_0 << 8), na = bp_0[3] + (bp_0[2] << 8), cca < na + 4)
            || na + off > scanline )
          {
bad:
            TIFFErrorExt(tif->tif_clientdata, "NeXTDecode", "Not enough data for scanline %ld", tif->tif_row);
            return 0;
          }
          std::allocator_traits<std::allocator<std::__tree_node<std::__value_type<unsigned short,_IO_FILE *>,void *>>>::deallocate[abi:nn200000](
            &row[off],
            bp_0 + 4,
            na);
          bp_0 += na + 4;
          cca -= na + 4;
        }
        else
        {
          npixels = 0;
          imagewidth = tif->tif_dir.td_imagewidth;
          if ( (tif->tif_flags & 0x400) != 0 )
            imagewidth = tif->tif_dir.td_tilewidth;
          opa = row;
          while ( 1 )
          {
            grey = (n >> 6) & 3;
            nb = n & 0x3F;
            while ( 1 )
            {
              v7 = nb--;
              v12 = 0;
              if ( v7 > 0 )
                v12 = npixels < imagewidth;
              if ( !v12 )
                break;
              v8 = npixels++;
              switch ( v8 & 3 )
              {
                case 0:
                  *opa = grey << 6;
                  break;
                case 1:
                  *opa |= 16 * grey;
                  break;
                case 2:
                  *opa |= 4 * grey;
                  break;
                case 3:
                  v9 = opa++;
                  *v9 |= grey;
                  break;
                default:
                  continue;
              }
            }
            if ( npixels >= imagewidth )
              break;
            if ( !cca )
              goto bad;
            v10 = bp_0++;
            n = *v10;
            --cca;
          }
        }
      }
      else
      {
        if ( cca < scanline )
          goto bad;
        std::allocator_traits<std::allocator<std::__tree_node<std::__value_type<unsigned short,_IO_FILE *>,void *>>>::deallocate[abi:nn200000](
          row,
          bp_0,
          scanline);
        bp_0 += scanline;
        cca -= scanline;
      }
      occa -= scanline;
    }
  }
  TIFFErrorExt(tif->tif_clientdata, "NeXTDecode", "Fractional scanlines cannot be read");
  return 0;
}