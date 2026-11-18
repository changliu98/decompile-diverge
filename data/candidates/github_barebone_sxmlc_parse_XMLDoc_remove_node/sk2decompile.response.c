int XMLDoc_remove_node(XMLDoc* doc, int index, int free_node) {
  XMLNode** new_nodes;
  if (doc == NULL || doc->init_value != 0x19770522 || index < 0 ||
      index > doc->n_nodes)
    return 0;
  if (doc->n_nodes == 1)
    new_nodes = NULL;
  else {
    new_nodes = (XMLNode**)malloc(sizeof(XMLNode*) * (doc->n_nodes - 1));
    if (new_nodes == NULL) return 0;
  }
  XMLNode_free(doc->nodes[index]);
  if (free_node) free(doc->nodes[index]);
  if (new_nodes != NULL) {
    memcpy(new_nodes, &doc->nodes[index], index * sizeof(XMLNode*));
    memcpy(&new_nodes[index], &doc->nodes[index + 1],
           (doc->n_nodes - index - 1) * sizeof(XMLNode*));
  }
  if (doc->nodes != NULL) free(doc->nodes);
  doc->nodes = new_nodes;
  doc->n_nodes--;
  return 1;
}