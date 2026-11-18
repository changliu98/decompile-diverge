MOBI_RET __cdecl mobi_decompress_huffman_internal(
        MOBIBuffer *buf_out,
        MOBIBuffer *buf_in,
        const MOBIHuffCdic *huffcdic,
        size_t depth)
{
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
  
  if ( depth > 0x14 )
    return 3;
    
  ret = MOBI_SUCCESS;
  bitcount = 32;
  bitsleft = 8 * buf_in->maxlen;
  code_length = 0;
  buffer = mobi_buffer_fill64(buf_in);
  
  while ( ret == MOBI_SUCCESS )
  {
    if ( bitcount <= 0 )
    {
      bitcount += 32;
      buffer = mobi_buffer_fill64(buf_in);
    }
    
    code = buffer >> bitcount;
    t1 = huffcdic->table1[HIBYTE(code)];
    code_length = t1 & 0x1F;
    maxcode = (((t1 >> 8) + 1) << (32 - (t1 & 0x1F))) - 1;
    
    if ( (t1 & 0x80) == 0 )
    {
      while ( code < huffcdic->mincode_table[code_length] )
        ++code_length;
      maxcode = huffcdic->maxcode_table[code_length];
    }
    
    bitcount -= code_length;
    bitsleft -= code_length;
    if ( bitsleft < 0 )
      break;
      
    index = (maxcode - code) >> (32 - code_length);
    cdic_index = index >> huffcdic->code_length;
    
    if ( index >= huffcdic->index_count )
      return 3;
      
    offset = huffcdic->symbol_offsets[index];
    symbol_length = huffcdic->symbols[cdic_index][offset + 1] | (huffcdic->symbols[cdic_index][offset] << 8);
    is_decompressed = symbol_length >> 15;
    symbol_length &= 0x7FFFu;
    
    if ( is_decompressed )
    {
      mobi_buffer_addraw(buf_out, &huffcdic->symbols[cdic_index][offset + 2], symbol_length);
      ret = buf_out->error;
    }
    else
    {
      buf_sym.data = &huffcdic->symbols[cdic_index][offset + 2];
      buf_sym.offset = 0LL;
      buf_sym.maxlen = symbol_length;
      buf_sym.error = MOBI_SUCCESS;
      ret = mobi_decompress_huffman_internal(buf_out, &buf_sym, huffcdic, depth + 1);
    }
  }
  
  return ret;
}