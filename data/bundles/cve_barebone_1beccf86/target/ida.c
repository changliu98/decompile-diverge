int __cdecl FileSwfDecompression(
        const uint8_t *buffer,
        uint32_t buffer_len,
        DetectEngineThreadCtx *det_ctx,
        InspectionBuffer *out_buffer,
        int swf_type,
        uint32_t decompress_depth,
        uint32_t compress_depth)
{
  uint8_t *v7; // rdi
  const uint8_t *v8; // rax
  uint8_t *compressed_data; // [rsp+0h] [rbp-70h] BYREF
  uint32_t v11; // [rsp+8h] [rbp-68h]
  unsigned __int64 __vla_expr0; // [rsp+10h] [rbp-60h]
  uint8_t **p_compressed_data; // [rsp+18h] [rbp-58h]
  uint32_t decompressed_data_len; // [rsp+24h] [rbp-4Ch]
  uint32_t decompressed_swf_len; // [rsp+28h] [rbp-48h]
  uint8_t swf_version; // [rsp+2Fh] [rbp-41h]
  uint32_t compressed_data_len; // [rsp+30h] [rbp-40h]
  uint32_t offset; // [rsp+34h] [rbp-3Ch]
  int compression_type; // [rsp+38h] [rbp-38h]
  int r; // [rsp+3Ch] [rbp-34h]
  uint32_t decompress_deptha; // [rsp+40h] [rbp-30h]
  int swf_typea; // [rsp+44h] [rbp-2Ch]
  InspectionBuffer *out_buffera; // [rsp+48h] [rbp-28h]
  DetectEngineThreadCtx *det_ctxa; // [rsp+50h] [rbp-20h]
  uint32_t buffer_lena; // [rsp+5Ch] [rbp-14h]
  const uint8_t *buffera; // [rsp+60h] [rbp-10h]

  buffera = buffer;
  buffer_lena = buffer_len;
  det_ctxa = det_ctx;
  out_buffera = out_buffer;
  swf_typea = swf_type;
  decompress_deptha = decompress_depth;
  r = 0;
  compression_type = FileIsSwfFile(buffer, buffer_len);
  if ( compression_type != 1 )
  {
    offset = 0;
    if ( compression_type == 2 )
    {
      offset = 8;
    }
    else if ( compression_type == 3 )
    {
      offset = 17;
    }
    if ( buffer_lena <= offset )
    {
      DetectEngineSetEvent(det_ctxa, 1u);
      return 0;
    }
    compressed_data_len = 0;
    if ( compress_depth && compress_depth <= buffer_lena - offset )
      compressed_data_len = compress_depth;
    else
      compressed_data_len = buffer_lena - offset;
    swf_version = FileGetSwfVersion(buffera, buffer_lena);
    if ( compression_type == 2 && swf_version < 6u || compression_type == 3 && swf_version < 0xDu )
    {
      DetectEngineSetEvent(det_ctxa, 2u);
      return 0;
    }
    decompressed_swf_len = FileGetSwfDecompressedLen(buffera, buffer_lena);
    if ( !decompressed_swf_len )
      decompressed_swf_len = 2920;
    if ( decompress_deptha )
      v11 = decompress_deptha;
    else
      v11 = decompressed_swf_len;
    decompressed_data_len = v11 + 8;
    SCInspectionBufferCheckAndExpand(out_buffera, v11 + 8);
    if ( out_buffera->size < v11 + 8 )
    {
      DetectEngineSetEvent(det_ctxa, 3u);
      return 0;
    }
    out_buffera->len = decompressed_data_len;
    *out_buffera->buf = 70;
    out_buffera->buf[1] = 87;
    out_buffera->buf[2] = 83;
    out_buffera->buf[3] = swf_version;
    *((_DWORD *)out_buffera->buf + 1) = decompressed_swf_len;
    memset(out_buffera->buf + 8, 0, decompressed_data_len - 8);
    if ( (swf_typea == 1 || swf_typea == 3) && compression_type == 2 )
    {
      r = FileSwfZlibDecompression(
            det_ctxa,
            (uint8_t *)&buffera[offset],
            compressed_data_len,
            out_buffera->buf + 8,
            out_buffera->len - 8);
      if ( r )
      {
LABEL_39:
        out_buffera->inspect = out_buffera->buf;
        out_buffera->inspect_len = out_buffera->len;
        return 1;
      }
    }
    else if ( (swf_typea == 2 || swf_typea == 3) && compression_type == 3 )
    {
      compressed_data_len += 13;
      p_compressed_data = &compressed_data;
      v7 = (uint8_t *)&compressed_data - ((compressed_data_len + 15LL) & 0xFFFFFFFFFFFFFFF0LL);
      compressed_data = v7;
      __vla_expr0 = compressed_data_len;
      v8 = buffera;
      *(_DWORD *)v7 = *((_DWORD *)buffera + 3);
      v7[4] = v8[16];
      memset(v7 + 5, 255, 8uLL);
      memcpy(compressed_data + 13, &buffera[offset], compressed_data_len - 13);
      r = FileSwfLzmaDecompression(
            det_ctxa,
            compressed_data,
            compressed_data_len,
            out_buffera->buf + 8,
            out_buffera->len - 8);
      if ( !(r ? 0 : 2) )
        goto LABEL_39;
    }
    return 0;
  }
  return 0;
}