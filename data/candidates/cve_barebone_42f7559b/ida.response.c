MOBI_RET __cdecl mobi_decompress_huffman_internal(
        MOBIBuffer *buf_out,
        MOBIBuffer *buf_in,
        const MOBIHuffCdic *huffcdic,
        size_t depth)
{
  MOBIBuffer buf_sym; // [rsp+0h] [rbp-80h] BYREF
  int is_decompressed; // [rsp+20h] [rbp-60h]
  uint32_t symbol_length; // [rsp+24h] [rbp-5Ch]
  uint32_t offset; // [rsp+28h] [rbp-58h]
  uint16_t cdic_index; // [rsp+2Eh] [rbp-52h]
  uint32_t index; // [rsp+30h] [rbp-50h]
  uint32_t maxcode; // [rsp+34h] [rbp-4Ch]
  uint32_t t1; // [rsp+38h] [rbp-48h]
  uint32_t code; // [rsp+3Ch] [rbp-44h]
  uint64_t buffer; // [rsp+40h] [rbp-40h]
  uint8_t code_length; // [rsp+4Bh] [rbp-35h]
  int bitsleft; // [rsp+4Ch] [rbp-34h]
  int8_t bitcount; // [rsp+53h] [rbp-2Dh]
  MOBI_RET ret; // [rsp+54h] [rbp-2Ch]
  size_t deptha; // [rsp+58h] [rbp-28h]
  const MOBIHuffCdic *huffcdica; // [rsp+60h] [rbp-20h]
  MOBIBuffer *buf_ina; // [rsp+68h] [rbp-18h]
  MOBIBuffer *buf_outa; // [rsp+70h] [rbp-10h]

  buf_outa = buf_out;
  buf_ina = buf_in;
  huffcdica = huffcdic;
  deptha = depth;
  if ( depth > 0x14 )
    return 3;
  ret = MOBI_SUCCESS;
  bitcount = 32;
  bitsleft = 8 * buf_ina->maxlen;
  code_length = 0;
  buffer = mobi_buffer_fill64(buf_ina);
  while ( ret == MOBI_SUCCESS )
  {
    if ( bitcount <= 0 )
    {
      bitcount += 32;
      buffer = mobi_buffer_fill64(buf_ina);
    }
    code = buffer >> bitcount;
    t1 = huffcdica->table1[HIBYTE(code)];
    code_length = t1 & 0x1F;
    maxcode = (((t1 >> 8) + 1) << (32 - (t1 & 0x1F))) - 1;
    if ( (t1 & 0x80) == 0 )
    {
      while ( code < huffcdica->mincode_table[code_length] )
        ++code_length;
      maxcode = huffcdica->maxcode_table[code_length];
    }
    bitcount -= code_length;
    bitsleft -= code_length;
    if ( bitsleft < 0 )
      break;
    index = (maxcode - code) >> (32 - code_length);
    cdic_index = index >> huffcdica->code_length;
    if ( index >= huffcdica->index_count )
      return 3;
    offset = huffcdica->symbol_offsets[index];
    symbol_length = huffcdica->symbols[cdic_index][offset + 1] | (huffcdica->symbols[cdic_index][offset] << 8);
    is_decompressed = symbol_length >> 15;
    symbol_length &= 0x7FFFu;
    if ( is_decompressed )
    {
      mobi_buffer_addraw(buf_outa, &huffcdica->symbols[cdic_index][offset + 2], symbol_length);
      ret = buf_outa->error;
    }
    else
    {
      buf_sym.data = &huffcdica->symbols[cdic_index][offset + 2];
      buf_sym.offset = 0LL;
      buf_sym.maxlen = symbol_length;
      buf_sym.error = MOBI_SUCCESS;
      ret = mobi_decompress_huffman_internal(buf_outa, &buf_sym, huffcdica, deptha + 1);
    }
  }
  return ret;
}