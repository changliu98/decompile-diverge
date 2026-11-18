int XMLNode_remove_attribute(XMLNode *node, int i_attr)
{
 XMLAttribute *new_attributes = NULL;

 if (node == NULL || node->init_value != 0x19770522 || i_attr < 0 || i_attr >= node->n_attributes)
  return -1;

 if (node->n_attributes > 1) {
  new_attributes = (XMLAttribute *)malloc((size_t)(node->n_attributes - 1) * sizeof(XMLAttribute));
  if (new_attributes == NULL)
   return -1;
 }

 if (node->attributes[i_attr].name != NULL)
  free(node->attributes[i_attr].name);
 if (node->attributes[i_attr].value != NULL)
  free(node->attributes[i_attr].value);

 if (new_attributes != NULL) {
  memcpy(new_attributes, node->attributes, (size_t)i_attr * sizeof(XMLAttribute));
  memcpy(new_attributes + i_attr, node->attributes + i_attr + 1, (size_t)(node->n_attributes - i_attr - 1) * sizeof(XMLAttribute));
 }

 if (node->attributes != NULL)
  free(node->attributes);
 node->attributes = new_attributes;
 node->n_attributes--;

 return node->n_attributes;
}