int remove_attribute(struct _XMLNode *node, int i_attr)
{
  if (node == ((void *)0) || node->init_value != 0x19991999 ||
      i_attr < 0 || i_attr >= node->n_attributes)
    return -1;
  struct _XMLAttribute *new_attributes = ((void *)0);
  if (node->n_attributes > 1) {
    new_attributes = (struct _XMLAttribute *)
      xmalloc(sizeof(XMLAttribute)*(node->n_attributes-1));
    if (new_attributes == ((void *)0))
      return -1;
  }
  if (node->attributes[i_attr].name != ((void *)0))
    xfree(node->attributes[i_attr].name);
  if (node->attributes[i_attr].value != ((void *)0))
    xfree(node->attributes[i_attr].value);
  if (new_attributes != ((void *)0)) {
    memcpy(new_attributes, node->attributes,
           sizeof(XMLAttribute)*i_attr);
    memcpy(&new_attributes[i_attr],
           &node->attributes[i_attr+1],
           sizeof(XMLAttribute)*(node->n_attributes - i_attr - 1));
  }
  if (node->attributes != ((void *)0))
    xfree(node->attributes);
  node->attributes = new_attributes;
  node->n_attributes -= 1;
  return node->n_attributes;
}