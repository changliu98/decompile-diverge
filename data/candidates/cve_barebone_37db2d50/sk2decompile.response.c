MOBI_RET mobi_decompress_huffman_internal(MOBIHuffman *huffman,
                                          MOBIHuffman *huffman_in,
                                          const MOBIHuffmanTree *huffman_tree,
                                          unsigned int depth) {
  if (depth > 20) {
    return 3;
  }
  MOBI_RET ret = MOBI_SUCCESS;
  int8_t shift = 32;
  int bits_left = 8 * huffman_in->size;
  unsigned char code_length = 0;
  unsigned long long code = mobi_buffer_fill64(huffman_in);
  while (ret == MOBI_SUCCESS) {
    if (shift <= 0) {
      shift += 32;
      code = mobi_buffer_fill64(huffman_in);
    }
    unsigned int code_in = code >> shift;
    unsigned int code_length_table = huffman_tree->code_length_table[code_in >> 24];
    code_length = code_length_table & 0x1F;
    unsigned int code_max = ((code_length_table >> 8) + 1) << (32 - code_length);
    code_max -= 1;
    if ((code_length_table & 0x80) == 0) {
      while (code_in < huffman_tree->code_value[code_length]) {
        code_length++;
      }
      code_max = huffman_tree->code_max[code_length];
    }
    shift -= code_length;
    bits_left -= code_length;
    if (bits_left < 0) {
      break;
    }
    unsigned int code_index = (code_max - code_in) >> (32 - code_length);
    unsigned short table_index = code_index >> huffman_tree->table_shift;
    if (code_index >= huffman_tree->table_size) {
      return 3;
    }
    unsigned int offset = huffman_tree->table[code_index];
    unsigned int low = huffman_tree->table_data[table_index][offset];
    unsigned int high = huffman_tree->table_data[table_index][offset + 1];
    unsigned int value = (high << 8) | low;
    int is_leaf = value >> 15;
    value &= 0x7FFF;
    if (is_leaf) {
      mobi_buffer_addraw(huffman,
                         huffman_tree->table_data[table_index] + offset + 2,
                         value);
      ret = huffman->ret;
    } else {
      MOBIHuffman huffman_new = {huffman_tree->table_data[table_index] + offset +
                                     2,
                                 0,
                                 value,
                                 MOBI_SUCCESS};
      ret = mobi_decompress_huffman_internal(huffman, &huffman_new, huffman_tree,
                                             depth + 1);
    }
  }
  return ret;
}