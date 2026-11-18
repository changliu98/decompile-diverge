int FileSwfDecompression(unsigned char *data, int data_len, struct _DetectEngineThreadCtx *ctx, struct _InspectionBuffer *out_buf, int swf_type, int decompress_depth, int compress_depth)
{
  int compression_type = detect_engine_get_compression_type(data, data_len);
  int offset = 0;
  int decompress_len = 0;
  int decompress_data_len = 0;
  int decompress_swf_len = 0;
  int decompress_ret = 0;
  if (compression_type == 1)
  {
    return 0;
  }
  if (compression_type == 2)
  {
    offset = 8;
  }
  else if (compression_type == 3)
  {
    offset = 17;
  }
  if (data_len <= offset)
  {
    detect_engine_set_error(ctx, 1);
    return 0;
  }
  decompress_len = 0;
  if (compress_depth == 0 || compress_depth > (data_len - offset))
  {
    decompress_len = (data_len - offset);
  }
  else
  {
    decompress_len = compress_depth;
  }
  unsigned char swf_version = detect_engine_get_swf_version(data, data_len);
  if (compression_type == 2 && (swf_version < 6) || compression_type == 3 && (swf_version < 13))
  {
    detect_engine_set_error(ctx, 2);
    return 0;
  }
  decompress_swf_len = detect_engine_get_decompress_swf_len(data, data_len);
  if (decompress_swf_len == 0)
  {
    decompress_swf_len = 2920;
  }
  if (decompress_depth == 0)
  {
    decompress_data_len = decompress_swf_len + 8;
  }
  else
  {
    decompress_data_len = decompress_depth + 8;
  }
  inspection_buffer_set_size(out_buf, decompress_data_len);
  if (out_buf->size < decompress_data_len)
  {
    detect_engine_set_error(ctx, 3);
    return 0;
  }
  out_buf->len = decompress_data_len;
  out_buf->buf[0] = 'F';
  out_buf->buf[1] = 'W';
  out_buf->buf[2] = 'S';
  out_buf->buf[3] = swf_version;
  memcpy(out_buf->buf + 4, decompress_swf_len, sizeof(decompress_swf_len));
  random_fill(out_buf->buf + 8, 0, decompress_data_len - 8);
  if (swf_type == 1 || swf_type == 3)
  {
    if (compression_type == 2)
    {
      decompress_ret = detect_engine_decompress_swf1(ctx, data + offset, decompress_len, out_buf->buf + 8, out_buf->len - 8);
      if (decompress_ret != 0)
      {
        goto success;
      }
    }
  }
  else if (swf_type == 2 || swf_type == 3)
  {
    if (compression_type == 3)
    {
      decompress_len += 13;
      unsigned char *decompress_data = (uint8_t *)((uint32_t)(decompress_data + decompress_len) & ~((uint32_t)15));
      memcpy(decompress_data, data + 12, sizeof(decompress_data));
      random_fill(decompress_data + 13, 0xff, sizeof(decompress_data) - 13);
      detect_engine_decompress_swf2(decompress_data + 13, data + offset, decompress_len - 13);
      decompress_ret = detect_engine_decompress_swf3(ctx, decompress_data, decompress_len, out_buf->buf + 8, out_buf->len - 8);
      if (decompress_ret == 0)
      {
        goto success;
      }
    }
  }
  return 0;
success:
  out_buf->inspect = out_buf->buf;
  out_buf->inspect_len = out_buf->len;
  return 1;
}