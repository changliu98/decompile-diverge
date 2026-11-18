static void ezxml_char_content(ezxml_t xml, char *buf, int len, char decode) {
  ezxml_node_t node = xml->parent;
  char *decoded;
  int decoded_len;
  if (!node || !node->name || len == 0) return;
  buf[len] = 0;
  decoded = ezxml_decode(buf, xml->encoding, decode);
  decoded_len = strlen(decoded) + 1;
  if (node->txt[0]) {
    int txt_len = strlen(node->txt);
    if (node->flags & 64)
      node->txt = realloc(node->txt, txt_len + decoded_len);
    else
      node->txt = strcpy(malloc(txt_len + decoded_len), node->txt);
    strcpy(node->txt + txt_len, decoded);
    if (decoded != buf) free(decoded);
  } else
    node->txt = decoded;
  if (node->txt != buf) ezxml_set_flag(node, 64);
}