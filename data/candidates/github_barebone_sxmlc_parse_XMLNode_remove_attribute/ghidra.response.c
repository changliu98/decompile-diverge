int XMLNode_remove_attribute(XMLNode *node,int i_attr)

{
  XMLAttribute *pt;
  int i_attr_local;
  XMLNode *node_local;
  int local_c;
  
  if ((((node == (XMLNode *)0x0) || (node->init_value != 0x19770522)) || (i_attr < 0)) ||
     (node->n_attributes <= i_attr)) {
    local_c = -1;
  }
  else {
    if (node->n_attributes == 1) {
      pt = (XMLAttribute *)0x0;
    }
    else {
      pt = malloc((long)(node->n_attributes + -1) * 0x18);
      if (pt == (XMLAttribute *)0x0) {
        return -1;
      }
    }
    if (node->attributes[i_attr].name != (SXML_CHAR *)0x0) {
      free(node->attributes[i_attr].name);
    }
    if (node->attributes[i_attr].value != (SXML_CHAR *)0x0) {
      free(node->attributes[i_attr].value);
    }
    if (pt != (XMLAttribute *)0x0) {
      memcpy(pt,node->attributes,(long)i_attr * 0x18);
      memcpy(pt + i_attr,node->attributes + (i_attr + 1),
             (long)((node->n_attributes - i_attr) + -1) * 0x18);
    }
    if (node->attributes != (XMLAttribute *)0x0) {
      free(node->attributes);
    }
    node->attributes = pt;
    node->n_attributes = node->n_attributes + -1;
    local_c = node->n_attributes;
  }
  return local_c;
}