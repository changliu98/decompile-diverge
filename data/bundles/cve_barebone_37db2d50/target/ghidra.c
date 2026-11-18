MOBI_RET mobi_decompress_huffman_internal
                   (MOBIBuffer *buf_out,MOBIBuffer *buf_in,MOBIHuffCdic *huffcdic,size_t depth)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  MOBIBuffer buf_sym;
  int is_decompressed;
  uint32_t symbol_length;
  uint32_t offset;
  uint16_t cdic_index;
  uint32_t index;
  uint32_t maxcode;
  uint32_t t1;
  uint32_t code;
  uint64_t buffer;
  uint8_t code_length;
  int bitsleft;
  int8_t bitcount;
  MOBI_RET ret;
  size_t depth_local;
  MOBIHuffCdic *huffcdic_local;
  MOBIBuffer *buf_in_local;
  MOBIBuffer *buf_out_local;
  MOBI_RET local_c;
  
  if (depth < 0x15) {
    ret = MOBI_SUCCESS;
    bitcount = ' ';
    bitsleft = (int)(buf_in->maxlen << 3);
    buffer = mobi_buffer_fill64(buf_in);
    while (ret == MOBI_SUCCESS) {
      if (bitcount < '\x01') {
        bitcount = bitcount + ' ';
        buffer = mobi_buffer_fill64(buf_in);
      }
      uVar3 = (uint)(buffer >> (bitcount & 0x3fU));
      uVar2 = huffcdic->table1[uVar3 >> 0x18];
      code_length = (byte)uVar2 & 0x1f;
      maxcode = ((uVar2 >> 8) + 1 << (0x20 - code_length & 0x1f)) - 1;
      if ((uVar2 & 0x80) == 0) {
        for (; uVar3 < huffcdic->mincode_table[code_length]; code_length = code_length + '\x01') {
        }
        maxcode = huffcdic->maxcode_table[code_length];
      }
      bitcount = bitcount - code_length;
      bitsleft = bitsleft - (uint)code_length;
      if (bitsleft < 0) break;
      uVar2 = maxcode - uVar3 >> (0x20 - code_length & 0x1f);
      uVar1 = (ushort)(uVar2 >> ((byte)huffcdic->code_length & 0x1f));
      if (huffcdic->index_count <= (ulong)uVar2) {
        return MOBI_DATA_CORRUPT;
      }
      uVar2 = (uint)huffcdic->symbol_offsets[uVar2];
      uVar3 = CONCAT11(huffcdic->symbols[uVar1][uVar2],huffcdic->symbols[uVar1][uVar2 + 1]) & 0x7fff
      ;
      if ((char)huffcdic->symbols[uVar1][uVar2] < '\0') {
        mobi_buffer_addraw(buf_out,huffcdic->symbols[uVar1] + (ulong)uVar2 + 2,(ulong)uVar3);
        ret = buf_out->error;
      }
      else {
        buf_sym.data = huffcdic->symbols[uVar1] + (ulong)uVar2 + 2;
        buf_sym.offset = 0;
        buf_sym.maxlen = (size_t)uVar3;
        buf_sym.error = MOBI_SUCCESS;
        ret = mobi_decompress_huffman_internal(buf_out,&buf_sym,huffcdic,depth + 1);
      }
    }
    local_c = ret;
  }
  else {
    local_c = MOBI_DATA_CORRUPT;
  }
  return local_c;
}