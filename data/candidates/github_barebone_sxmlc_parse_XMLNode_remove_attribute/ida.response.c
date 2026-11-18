int __cdecl XMLNode_remove_attribute(XMLNode *node, int i_attr)
{
  XMLAttribute *pt; // [rsp+0h] [rbp-20h]

  if ( !node || node->init_value != 427230498 || i_attr < 0 || i_attr >= node->n_attributes )
    return -1;
  if ( node->n_attributes == 1 )
  {
    pt = 0LL;
  }
  else
  {
    pt = (XMLAttribute *)malloc(24LL * (node->n_attributes - 1));
    if ( !pt )
      return -1;
  }
  if ( node->attributes[i_attr].name )
    free(node->attributes[i_attr].name);
  if ( node->attributes[i_attr].value )
    free(node->attributes[i_attr].value);
  if ( pt )
  {
    memcpy(pt, node->attributes, 24LL * i_attr);
    memcpy(&pt[i_attr], &node->attributes[i_attr + 1], 24LL * (node->n_attributes - i_attr - 1));
  }
  if ( node->attributes )
    free(node->attributes);
  node->attributes = pt;
  return --node->n_attributes;
}