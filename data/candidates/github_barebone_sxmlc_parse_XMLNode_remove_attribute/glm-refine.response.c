int __cdecl XMLNode_remove_attribute(XMLNode *node, int i_attr)
{
  XMLAttribute *new_attributes;

  // Validate node, magic number ("XMLN"), and attribute index
  if (!node || node->init_value != 0x19701122 || i_attr < 0 || i_attr >= node->n_attributes)
    return -1;

  // If this is the only attribute, we just free the array. 
  // Otherwise, allocate a new array shrunk by 1 element.
  if (node->n_attributes == 1)
  {
    new_attributes = NULL;
  }
  else
  {
    new_attributes = (XMLAttribute *)malloc(sizeof(XMLAttribute) * (node->n_attributes - 1));
    if (!new_attributes)
      return -1;
  }

  // Free the strings owned by the attribute being removed
  if (node->attributes[i_attr].name)
    free(node->attributes[i_attr].name);
    
  if (node->attributes[i_attr].value)
    free(node->attributes[i_attr].value);

  // Copy the remaining attributes to the new array
  if (new_attributes)
  {
    // Copy elements before the removed attribute
    memcpy(new_attributes, node->attributes, sizeof(XMLAttribute) * i_attr);
    
    // Copy elements after the removed attribute
    memcpy(new_attributes + i_attr, 
           node->attributes + i_attr + 1, 
           sizeof(XMLAttribute) * (node->n_attributes - i_attr - 1));
  }

  // Free the old array and update the node
  if (node->attributes)
    free(node->attributes);
    
  node->attributes = new_attributes;
  
  return --node->n_attributes;
}