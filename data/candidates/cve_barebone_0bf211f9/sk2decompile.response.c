static int smacker_decode_tree(BitStreamReader *bs, SmackerTree *tree,
                               int code, int depth) {
  int ret;
  if (bitstream_read_bit(bs)) {
    ret = smacker_decode_tree(bs, tree, code, depth + 1);
    if (ret) return ret;
    return smacker_decode_tree(bs, tree, code | (1 << (depth + 1 - 1)),
                               depth + 1);
  } else {
    if (tree->size >= 256) {
      av_log(NULL, 16, "Tree size exceeded!\n");
      return 0xbcdef001;
    }
    if (depth) {
      tree->code[tree->size] = code;
      tree->depth[tree->size] = depth;
    } else {
      tree->code[tree->size] = 0;
      tree->depth[tree->size] = 0;
    }
    tree->value[tree->size] = bitstream_read(bs, 8);
    tree->size++;
    if (depth > tree->max_depth) tree->max_depth = depth;
    return 0;
  }
}