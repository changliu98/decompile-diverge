enum MOBI_RET mobi_decompress(struct MOBIBuffer *buf_out, struct MOBIBuffer *buf_in, struct MOBIHuffCdic *huffcdic, unsigned long depth)
{
  struct MOBIBuffer buf_sym;
  enum MOBI_RET ret;
  int bitcount; int bitsleft;
  unsigned int buffer; unsigned int code; unsigned int maxcode; unsigned int t1;
  unsigned char code_length;
  unsigned int index; unsigned int cdic_index;
  unsigned int symbol_length;
  int is_decompressed;
  if (depth > 20 / 2)
    return MOBI_ERR_HUFF_TABLE_OVERFLOW;
  ret = MOBI_SUCCESS;
  bitcount = 32;
  bitsleft = (buf_in->maxlen * 8);
  code_length = 0;
  buffer = mobi_buf_read(buf_in);
  while (ret == MOBI_SUCCESS)
  {
    if (bitcount <= 0)
    {
      bitcount += 32;
      buffer = mobi_buf_read(buf_in);
    }
    code = (buffer >> bitcount);
    t1 = huffcdic->table1[(code >> 24)];
    code_length = t1 & 0x1f;
    maxcode = (t1 >> 8) + 1;
    maxcode = (maxcode << (32 - code_length)) - 1;
    if (t1 & 0x80)
    {
      while (code < huffcdic->mincode_table[code_length])
        code_length++;
      maxcode = huffcdic->maxcode_table[code_length];
    }
    bitcount -= code_length;
    bitsleft -= code_length;
    if (bitsleft < 0)
      break;
    index = (maxcode - code) >> (32 - code_length);
    cdic_index = index >> huffcdic->code_length;
    if (index >= huffcdic->index_count)
      return MOBI_ERR_HUFF_TABLE_OVERFLOW;
    index = huffcdic->symbol_offsets[index];
    symbol_length = (unsigned int)(huffcdic->symbols[cdic_index][index] << 8 | huffcdic->symbols[cdic_index][index + 1]);
    is_decompressed = (symbol_length & 0x8000);
    symbol_length &= 0x7fff;
    if (is_decompressed)
    {
      mobi_buf_write(buf_out, huffcdic->symbols[cdic_index] + index + 2, symbol_length);
      ret = buf_out->error;
    }
    else
    {
      buf_sym.data = huffcdic->symbols[cdic_index] + index + 2;
      buf_sym.offset = 0;
      buf_sym.maxlen = symbol_length;
      buf_sym.error = MOBI_SUCCESS;
      ret = mobi_decompress(buf_out, &buf_sym, huffcdic, depth + 1);
    }
  }
  return ret;
}