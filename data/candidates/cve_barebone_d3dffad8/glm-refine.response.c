jp2_box_t *__cdecl jp2_box_get(jas_stream_t *in)
{
  uint_fast64_t extlen;
  uint_fast32_t len;
  jas_stream_t *tmpstream = NULL;
  jp2_boxinfo_t *boxinfo;
  jp2_box_t *box = NULL;
  jas_stream_t *ina = in;

  // Allocate the box structure (0x140 = 320 bytes)
  box = (jp2_box_t *)jas_malloc(0x140uLL);
  if (!box)
    goto error;

  // Assign default unknown box operations
  box->ops = (jp2_boxops_t *)((char *)&jp2_boxinfo_unk + 24);

  // Read the 4-byte length and 4-byte type from the stream
  if (jp2_getuint32(ina, &len) || jp2_getuint32(ina, &box->type))
    goto error;

  // Look up box info based on type and initialize box properties
  boxinfo = jp2_boxinfolookup(box->type);
  box->info = boxinfo;
  box->ops = &boxinfo->ops;
  box->len = len;

  // Debug logging for preliminary box processing
  if (jas_getdbglevel() >= 10)
  {
    jas_eprintf(
      "preliminary processing of JP2 box: type=%c%s%c (0x%08x); length=%d\n",
      34LL,
      boxinfo->name,
      34LL,
      box->type,
      box->len);
  }

  // Handle extended length (if len == 1, the next 8 bytes contain the real length)
  if (box->len == 1)
  {
    if (jp2_getuint64(ina, &extlen))
      goto error;

    // Clamp to 32-bit maximum if it exceeds limits
    if (extlen > 0xFFFFFFFF)
    {
      jas_eprintf("warning: cannot handle large 64-bit box length\n");
      extlen = 0xFFFFFFFFLL;
    }

    box->len = extlen;
    box->datalen = extlen - 16; // 4 (len) + 4 (type) + 8 (extlen)
  }
  else
  {
    box->datalen = box->len - 8; // 4 (len) + 4 (type)
  }

  // Validate length: if non-zero and less than 8, it's malformed
  if (box->len && box->len < 8)
    goto error;

  // Check if the box has a specific flag set (e.g., JP2_BOX_EXT_LENGTH or similar)
  // If flags & 3 are 0, proceed to parse the data payload
  if ((box->info->flags & 3) != 0)
    goto dump_and_return;

  // Open a temporary memory stream to hold the box data
  tmpstream = jas_stream_memopen(0LL, 0);
  if (!tmpstream)
    goto error;

  // Copy the box data from the input stream to the temporary stream
  if (jas_stream_copy(tmpstream, ina, box->datalen))
  {
    // Reset ops on failure, matching original decompilation
    box->ops = (jp2_boxops_t *)((char *)&jp2_boxinfo_unk + 24);
    jas_eprintf("cannot copy box data\n");
    goto error;
  }

  // Rewind the temporary stream for reading
  jas_stream_rewind(tmpstream);

  // If a getdata operation is defined, use it to parse the box data
  if (box->ops->getdata && box->ops->getdata(box, tmpstream))
  {
    jas_eprintf("cannot parse box data\n");
    goto error;
  }

  // Close the temporary stream after successful parsing
  jas_stream_close(tmpstream);
  tmpstream = NULL;

dump_and_return:
  // Dump box info if debug level is >= 1
  if (jas_getdbglevel() >= 1)
    jp2_box_dump(box, stderr);

  return box;

error:
  // Cleanup routine on failure
  if (box)
    jp2_box_destroy(box);
  if (tmpstream)
    jas_stream_close(tmpstream);
  
  return NULL;
}