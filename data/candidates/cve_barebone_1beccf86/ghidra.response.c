int FileSwfDecompression
              (uint8_t *buffer,uint32_t buffer_len,DetectEngineThreadCtx *det_ctx,
              InspectionBuffer *out_buffer,int swf_type,uint32_t decompress_depth,
              uint32_t compress_depth)

{
  uint32_t uVar1;
  long lVar2;
  uint32_t compressed_data_len_00;
  DetectEngineThreadCtx *det_ctx_00;
  int iVar3;
  uint uVar4;
  uint8_t *puVar5;
  uint8_t *puVar6;
  undefined8 uStack_80;
  undefined8 local_78;
  uint32_t local_70;
  unsigned_long __vla_expr0;
  undefined1 *local_60;
  uint32_t decompressed_data_len;
  uint32_t decompressed_swf_len;
  uint8_t swf_version;
  uint32_t compressed_data_len;
  uint32_t offset;
  int compression_type;
  int r;
  uint32_t decompress_depth_local;
  int swf_type_local;
  InspectionBuffer *out_buffer_local;
  DetectEngineThreadCtx *det_ctx_local;
  uint32_t buffer_len_local;
  uint8_t *buffer_local;
  
  r = 0;
  uStack_80 = 0x101235;
  decompress_depth_local = decompress_depth;
  swf_type_local = swf_type;
  out_buffer_local = out_buffer;
  det_ctx_local = det_ctx;
  buffer_len_local = buffer_len;
  buffer_local = buffer;
  compression_type = FileIsSwfFile(buffer,buffer_len);
  if (compression_type == 1) {
    return 0;
  }
  offset = 0;
  if (compression_type == 2) {
    offset = 8;
  }
  else if (compression_type == 3) {
    offset = 0x11;
  }
  if (buffer_len_local <= offset) {
    uStack_80 = 0x10129b;
    DetectEngineSetEvent(det_ctx_local,'\x01');
    return 0;
  }
  if ((compress_depth == 0) || (buffer_len_local - offset < compress_depth)) {
    compressed_data_len = buffer_len_local - offset;
  }
  else {
    compressed_data_len = compress_depth;
  }
  uStack_80 = 0x1012e9;
  swf_version = FileGetSwfVersion(buffer_local,buffer_len_local);
  if ((compression_type == 2) && (swf_version < 6)) {
    uStack_80 = 0x101311;
    DetectEngineSetEvent(det_ctx_local,'\x02');
    return 0;
  }
  if ((compression_type == 3) && (swf_version < 0xd)) {
    uStack_80 = 0x101342;
    DetectEngineSetEvent(det_ctx_local,'\x02');
    return 0;
  }
  uStack_80 = 0x10135a;
  decompressed_swf_len = FileGetSwfDecompressedLen(buffer_local,buffer_len_local);
  if (decompressed_swf_len == 0) {
    decompressed_swf_len = 0xb68;
  }
  if (decompress_depth_local == 0) {
    local_70 = decompressed_swf_len;
  }
  else {
    local_70 = decompress_depth_local;
  }
  decompressed_data_len = local_70 + 8;
  uStack_80 = 0x1013a4;
  SCInspectionBufferCheckAndExpand(out_buffer_local,decompressed_data_len);
  if (decompressed_data_len <= out_buffer_local->size) {
    out_buffer_local->len = decompressed_data_len;
    *out_buffer_local->buf = 'F';
    out_buffer_local->buf[1] = 'W';
    out_buffer_local->buf[2] = 'S';
    out_buffer_local->buf[3] = swf_version;
    *(uint32_t *)(out_buffer_local->buf + 4) = decompressed_swf_len;
    uStack_80 = 0x101434;
    memset(out_buffer_local->buf + 8,0,(ulong)(decompressed_data_len - 8));
    puVar5 = buffer_local;
    if (((swf_type_local == 1) || (swf_type_local == 3)) && (compression_type == 2)) {
      uStack_80 = 0x101480;
      iVar3 = FileSwfZlibDecompression
                        (det_ctx_local,buffer_local + offset,compressed_data_len,
                         out_buffer_local->buf + 8,out_buffer_local->len - 8);
    }
    else {
      if ((swf_type_local != 2) && (swf_type_local != 3)) {
        return 0;
      }
      if (compression_type != 3) {
        return 0;
      }
                    /* Unresolved local var: uint8_t[398] compressed_data@[???] */
      compressed_data_len = compressed_data_len + 0xd;
      __vla_expr0 = (unsigned_long)compressed_data_len;
      lVar2 = -(__vla_expr0 + 0xf & 0xfffffffffffffff0);
      local_78 = (uint8_t *)((long)&local_78 + lVar2);
      local_60 = (undefined1 *)&local_78;
      *(undefined4 *)local_78 = *(undefined4 *)(buffer_local + 0xc);
      *(uint8_t *)((long)&local_78 + lVar2 + 4) = puVar5[0x10];
      *(undefined8 *)((long)&uStack_80 + lVar2) = 0x101506;
      memset((void *)((long)&local_78 + lVar2 + 5),0xff,8);
      puVar6 = local_78 + 0xd;
      puVar5 = buffer_local + offset;
      uVar4 = compressed_data_len - 0xd;
      *(undefined8 *)((long)&uStack_80 + lVar2) = 0x101527;
      memcpy(puVar6,puVar5,(ulong)uVar4);
      det_ctx_00 = det_ctx_local;
      compressed_data_len_00 = compressed_data_len;
      puVar6 = local_78;
      puVar5 = out_buffer_local->buf;
      uVar1 = out_buffer_local->len;
      *(undefined8 *)((long)&uStack_80 + lVar2) = 0x10154f;
      iVar3 = FileSwfLzmaDecompression
                        (det_ctx_00,puVar6,compressed_data_len_00,puVar5 + 8,uVar1 - 8);
    }
    if (iVar3 == 0) {
      return 0;
    }
    out_buffer_local->inspect = out_buffer_local->buf;
    out_buffer_local->inspect_len = out_buffer_local->len;
    return 1;
  }
  uStack_80 = 0x1013c2;
  DetectEngineSetEvent(det_ctx_local,'\x03');
  return 0;
}