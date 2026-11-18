jp2_box_t * jp2_box_read(jas_stream_t *input_stream)
{
  uint_fast32_t box_length;
  uint_fast64_t extended_length;
  jp2_boxinfo_t *box_info;
  jp2_box_t *box_ptr;
  jas_stream_t *temp_stream;
  int result_code;

  // Allocate memory for the JP2 box structure
  box_ptr = jas_malloc(0x140);
  // Check if allocation failed
  if (box_ptr == (jp2_box_t *)0x0) {
    return (jp2_box_t *)0x0;
  }

  // Set default operations pointer
  box_ptr->ops = (jp2_boxops_s *)0x104598;
  // Read the box length from the stream
  result_code = jp2_getuint32(input_stream, &box_length);
  if (result_code != 0) goto cleanup;
  // Read the box type from the stream
  result_code = jp2_getuint32(input_stream, &box_ptr->type);
  if (result_code != 0) goto cleanup;

  // Look up box information based on the type
  box_info = jp2_boxinfolookup((int)box_ptr->type);
  box_ptr->info = box_info;
  // Update operations pointer based on box info
  box_ptr->ops = &box_info->ops;
  box_ptr->len = box_length;

  // Debug output for preliminary box processing if debug level is high enough
  if (9 < jas_getdbglevel()) {
    jas_eprintf("preliminary processing of JP2 box: type=%c%s%c (0x%08x); length=%d\n",
                0x22, box_info->name, 0x22, box_ptr->type, box_ptr->len);
  }

  // Handle 64-bit box length if the initial length is 1
  if (box_ptr->len == 1) {
    // Read the extended 64-bit length
    result_code = jp2_getuint32(input_stream, &extended_length);
    if (result_code != 0) goto cleanup;
    // Cap the length if it exceeds 32-bit max
    if (0xffffffff < extended_length) {
      jas_eprintf("warning: cannot handle large 64-bit box length\n");
      extended_length = 0xffffffff;
    }
    box_ptr->len = extended_length;
    // Calculate data length by subtracting the 16-byte header (8 for len/type, 8 for extlen)
    box_ptr->datalen = extended_length - 0x10;
  }
  else {
    // Calculate data length by subtracting the 8-byte header
    box_ptr->datalen = box_ptr->len - 8;
  }

  // Process box data if length is valid (non-zero and greater than 7)
  if ((box_ptr->len == 0) || (7 < box_ptr->len)) {
    // If the box info flags indicate it can be parsed, attempt to parse
    if ((box_ptr->info->flags & 3U) != 0) {
      // Debug dump if debug level is greater than 0
      if (0 < jas_getdbglevel()) {
        jp2_box_dump(box_ptr, *(FILE **)PTR_stderr_00103ff8);
      }
      return box_ptr;
    }
    // Create a memory stream to hold the box data
    temp_stream = jas_stream_memopen((char *)0x0, 0);
    if (temp_stream != (jas_stream_t *)0x0) {
      // Copy box data into the memory stream
      result_code = jas_stream_copy(temp_stream, input_stream, (int)box_ptr->datalen);
      if (result_code == 0) {
        // Rewind the memory stream to the beginning
        jas_stream_rewind(temp_stream);
        // Check if the box has a getdata function and call it
        if ((box_ptr->ops->getdata == (_func_int_jp2_box_t_ptr_jas_stream_t_ptr *)0x0) ||
            (result_code = (*box_ptr->ops->getdata)(box_ptr, temp_stream), result_code == 0)) {
          jas_stream_close(temp_stream);
          // Debug dump if debug level is greater than 0
          if (0 < jas_getdbglevel()) {
            jp2_box_dump(box_ptr, *(FILE **)PTR_stderr_00103ff8);
          }
          return box_ptr;
        }
        jas_eprintf("cannot parse box data\n");
      }
      else {
        // Reset operations pointer on error
        box_ptr->ops = (jp2_boxops_s *)0x104598;
        jas_eprintf("cannot copy box data\n");
      }
      jas_stream_close(temp_stream);
    }
  }

cleanup:
  // Clean up and destroy the box on error
  jp2_box_destroy(box_ptr);
  return (jp2_box_t *)0x0;
}