enum MOBI_RET mobi_decompress(struct MOBIBuffer *buf_out, struct MOBIBuffer *buf_in, struct MOBIHuffCdic *huffcdic, unsigned long depth)
{
  if (depth > 20)
    return MOBI_ERR_HUFFMAN;
  enum MOBI_RET ret = MOBI_SUCCESS;
  int bitcount = 32;
  int bitsleft = (buf_in->maxlen * 8);
  unsigned int code;
  unsigned int code_length = 0;
  unsigned int buffer = mobi_buf_get_uint32(buf_in);
  while (ret == MOBI_SUCCESS)
  {
    if (bitcount <= 0)
    {
      bitcount += 32;
      buffer = mobi_buf_get_uint32(buf_in);
    }
    code = (buffer >> bitcount);
    unsigned int table1 = huffcdic->table1[((code >> 24) & 0xff)];
    code_length = (table1 & 0x1f);
    unsigned int maxcode = ((table1 >> 8) + 1) << (32 - code_length);
    maxcode = maxcode - 1;
    if (table1 & 0x80)
    {
      bitcount -= code_length;
      continue;
    }
    while (code < huffcdic->mincode_table[code_length])
      code_length++;
    maxcode = huffcdic->maxcode_table[code_length];
    bitcount -= code_length;
    bitsleft -= code_length;
    if (bitsleft < 0)
      break;
    unsigned int index = (maxcode - code) >> (32 - code_length);
    unsigned int cdic_index = (index >> huffcdic->code_length);
    if (index >= huffcdic->index_count)
      return MOBI_ERR_HUFFMAN;
    unsigned int offset = huffcdic->symbol_offsets[index];
    unsigned int symbol = (huffcdic->symbols[cdic_index][offset] << 8) | huffcdic->symbols[cdic_index][offset + 1];
    int is_decompressed = (symbol >> 15);
    symbol = symbol & 0x7fff;
    if (is_decompressed)
    {
      mobi_buf_put_data(buf_out, &huffcdic->symbols[cdic_index][offset + 2], symbol);
      ret = buf_out->error;
    }
    else
    {
      struct MOBIBuffer buf_sym;
      buf_sym.data = &huffcdic->symbols[cdic_index][offset + 2];
      buf_sym.offset = 0;
      buf_sym.maxlen = symbol;
      buf_sym.error = MOBI_SUCCESS;
      ret = mobi_decompress(&buf_out, &buf_sym, huffcdic, depth + 1);
    }
  }
  return ret;
}