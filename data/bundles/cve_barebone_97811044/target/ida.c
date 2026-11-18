void __cdecl iwjpeg_scan_exif_ifd(iwjpegrcontext *rctx, iw_exif_state *e, uint32_t ifd)
{
  double v_dbl; // [rsp+10h] [rbp-30h] BYREF
  unsigned int v; // [rsp+18h] [rbp-28h] BYREF
  unsigned int tag_id; // [rsp+1Ch] [rbp-24h]
  unsigned int tag_pos; // [rsp+20h] [rbp-20h]
  unsigned int i; // [rsp+24h] [rbp-1Ch]
  unsigned int tag_count; // [rsp+28h] [rbp-18h]
  uint32_t ifda; // [rsp+2Ch] [rbp-14h]
  iw_exif_state *ea; // [rsp+30h] [rbp-10h]
  iwjpegrcontext *rctxa; // [rsp+38h] [rbp-8h]

  rctxa = rctx;
  ea = e;
  ifda = ifd;
  if ( ifd >= 8 && ifda <= ea->d_len - 18 )
  {
    tag_count = iw_get_ui16_e(&ea->d[ifda], ea->endian);
    if ( tag_count <= 0x3E8 )
    {
      for ( i = 0; i < tag_count; ++i )
      {
        tag_pos = 12 * i + ifda + 2;
        if ( tag_pos + 12 > ea->d_len )
          break;
        tag_id = iw_get_ui16_e(&ea->d[tag_pos], ea->endian);
        switch ( tag_id )
        {
          case 0x112u:
            if ( get_exif_tag_int_value(ea, tag_pos, &v) )
              rctxa->exif_orientation = v;
            break;
          case 0x11Au:
            if ( get_exif_tag_dbl_value(ea, tag_pos, &v_dbl) )
              rctxa->exif_density_x = v_dbl;
            break;
          case 0x11Bu:
            if ( get_exif_tag_dbl_value(ea, tag_pos, &v_dbl) )
              rctxa->exif_density_y = v_dbl;
            break;
          case 0x128u:
            if ( get_exif_tag_int_value(ea, tag_pos, &v) )
              rctxa->exif_density_unit = v;
            break;
          default:
            continue;
        }
      }
    }
  }
}