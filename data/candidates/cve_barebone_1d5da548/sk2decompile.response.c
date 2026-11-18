static RONode *get_complex_object(RONodeInfo *info, RBuffer *buf) {
  bool err = false;
  RONode *node = calloc(1, sizeof(RONode));
  if (!node) {
    return NULL;
  }
  unsigned real_len;
  if (info->version < 0xfc0d) {
    real_len = get_ut8(buf, &err);
  } else {
    real_len = get_st32(buf, &err);
  }
  if (err) {
    free(node);
    return NULL;
  }
  char *real = malloc(real_len + 1);
  if (!real) {
    return NULL;
  }
  if (rz_buf_read(buf, real, real_len) != real_len) {
    free(real);
    free(node);
    node = NULL;
    return NULL;
  }
  real[real_len] = '\0';
  unsigned imag_len;
  if (info->version < 0xfc0d) {
    imag_len = get_ut8(buf, &err);
  } else {
    imag_len = get_st32(buf, &err);
  }
  if (err) {
    return NULL;
  }
  char *imag = malloc(imag_len + 1);
  if (!imag) {
    return NULL;
  }
  if (rz_buf_read(buf, imag, imag_len) != imag_len) {
    free(real);
    free(imag);
    free(node);
    node = NULL;
    return NULL;
  }
  imag[imag_len] = '\0';
  node->type = RONodeTypeComplex;
  node->value = rz_str_newf("%s+%sj", real, imag);
  free(real);
  free(imag);
  if (!node->value) {
    free(node);
    node = NULL;
  }
  return node;
}