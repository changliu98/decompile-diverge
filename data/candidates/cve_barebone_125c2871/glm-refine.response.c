int __cdecl ff_amf_get_field_value(
        const uint8_t *data,
        const uint8_t *data_end,
        const uint8_t *name,
        uint8_t *dst,
        int dst_size)
{
  int namelen = strlen((const char *)name);
  const uint8_t *p = data;

  // Skip over any AMF array elements (type 0x03) that precede the object
  while (1)
  {
    bool is_array = (*p == 3);
    if (!is_array && p >= data_end)
      break;

    int len = ff_amf_tag_size(p, data_end);
    if (len < 0)
      len = (int)(data_end - p);
    p += len;
  }

  // Ensure we have enough data for the AMF object marker (0x03) and ECMA array length (4 bytes)
  if (data_end - p < 3)
    return -1;

  p++; // Skip AMF object/array marker

  // Iterate through the AMF object properties
  while (1)
  {
    p += 2;
    int key_len = p[-1] | (p[-2] << 8); // Read 16-bit big-endian key length

    if (!key_len)
      return -1; // Empty key length indicates end of AMF object

    if (key_len < 0 || key_len >= data_end - p)
      return -1; // Out of bounds

    p += key_len;

    // Check if the current key matches the requested field name
    if (key_len == namelen && !memcmp(p - key_len, name, namelen))
      break;

    // Key doesn't match; skip the value associated with this key
    int val_len = ff_amf_tag_size(p, data_end);
    if (val_len < 0 || val_len >= data_end - p)
      return -1;
    p += val_len;
  }

  // Key matched; read the value type marker
  uint8_t type = *p++;

  if (type == 0) // AMF Number (64-bit double)
  {
    // Read 8 bytes, swap from big-endian to host endian, and format as a float
    uint64_t val = _byteswap_uint64(*(const uint64_t *)p);
    double dval;
    memcpy(&dval, &val, sizeof(double)); // Safe type punning
    snprintf((char *)dst, dst_size, "%g", dval);
  }
  else if (type == 1) // AMF Boolean
  {
    const char *val = *p ? "true" : "false";
    snprintf((char *)dst, dst_size, "%s", val);
  }
  else if (type == 2) // AMF String
  {
    p += 2;
    int str_len = p[-1] | (p[-2] << 8); // Read 16-bit big-endian string length

    int copy_len;
    if (str_len + 1 <= dst_size)
      copy_len = str_len + 1;
    else
      copy_len = dst_size;

    av_strlcpy((char *)dst, (const char *)p, copy_len);
  }
  else
  {
    return -1; // Unsupported AMF type
  }

  return 0;
}