int smacker_decode_tree(struct BitstreamContext *stream, struct HuffContext *context, unsigned int prefix, int length)
{
  int r;
  if (is_end_of_bitstream(stream)) {
    length += 1;
    r = smacker_decode_tree(stream, context, prefix, length);
    if (r)
      return r;
    return smacker_decode_tree(stream, context, (prefix << (length - 1)) | 1, length);
  }
  if (context->current >= 256) {
    log_print(((void *)0), 16, "Tree size exceeded!\n");
    return -1094995529;
  }
  if (length == 0) {
    context->bits[context->current] = 0;
    context->lengths[context->current] = 0;
  }
  else {
    context->bits[context->current] = prefix;
    context->lengths[context->current] = length;
  }
  context->values[context->current] = read_bits(stream, 8);
  context->current += 1;
  if (context->maxlength < length)
    context->maxlength = length;
  return 0;
}