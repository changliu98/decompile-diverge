int XMLNode_remove_attribute(XMLNode* node, int index) {
  XMLAttribute* new_attributes;
  if (node == NULL || node->init_value != 0x19770522 || index < 0 ||
      index >= node->n_attributes)
    return -1;
  if (node->n_attributes == 1)
    new_attributes = NULL;
  else {
    new_attributes =
        (XMLAttribute*)malloc((node->n_attributes - 1) * sizeof(XMLAttribute));
    if (new_attributes == NULL) return -1;
  }
  if (node->attributes[index].name != NULL) free(node->attributes[index].name);
  if (node->attributes[index].value != NULL)
    free(node->attributes[index].value);
  if (new_attributes != NULL) {
    memcpy(new_attributes, node->attributes, index * sizeof(XMLAttribute));
    memcpy(new_attributes + index, node->attributes + index + 1,
           (node->n_attributes - index - 1) * sizeof(XMLAttribute));
  }
  if (node->attributes != NULL) free(node->attributes);
  node->attributes = new_attributes;
  node->n_attributes--;
  return node->n_attributes;
}