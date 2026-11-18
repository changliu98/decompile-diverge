void __cdecl iwjpeg_scan_exif_ifd(iwjpegrcontext *rctx, iw_exif_state *e, uint32_t ifd)
{
  double v_dbl; 
  unsigned int v; 
  unsigned int tag_id; 
  unsigned int tag_pos; 
  unsigned int i; 
  unsigned int tag_count; 

  // Basic bounds check: IFD must start at least at offset 8 and leave room for 18 bytes
  if (ifd >= 8 && ifd <= e->d_len - 18)
  {
    // Read the number of IFD entries (each entry is 12 bytes)
    tag_count = iw_get_ui16_e(&e->d[ifd], e->endian);
    
    // Prevent infinite loops or oversized allocations by capping tag count to 1000
    if (tag_count <= 0x3E8)
    {
      for (i = 0; i < tag_count; ++i)
      {
        // Calculate the offset of the current IFD entry
        tag_pos = 12 * i + ifd + 2;
        
        // Bounds check for the 12-byte IFD entry
        if (tag_pos + 12 > e->d_len)
          break;
          
        tag_id = iw_get_ui16_e(&e->d[tag_pos], e->endian);
        switch (tag_id)
        {
          case 0x112: // Orientation
            if (get_exif_tag_int_value(e, tag_pos, &v))
              rctx->exif_orientation = v;
            break;
          case 0x11A: // XResolution
            if (get_exif_tag_dbl_value(e, tag_pos, &v_dbl))
              rctx->exif_density_x = v_dbl;
            break;
          case 0x11B: // YResolution
            if (get_exif_tag_dbl_value(e, tag_pos, &v_dbl))
              rctx->exif_density_y = v_dbl;
            break;
          case 0x128: // ResolutionUnit
            if (get_exif_tag_int_value(e, tag_pos, &v))
              rctx->exif_density_unit = v;
            break;
          default:
            continue;
        }
      }
    }
  }
}