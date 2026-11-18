int XMLDoc_remove_node(XMLDoc *doc,int i_node,int free_node)
{
 XMLNode **pt;

 if (doc == NULL || doc->init_value != 0x19770522 || i_node < 0 || i_node > doc->n_nodes)
  return 0;

 if (doc->n_nodes == 1)
  pt = NULL;
 else {
  pt = (XMLNode **)malloc((size_t)(doc->n_nodes - 1) * sizeof(XMLNode *));
  if (pt == NULL)
   return 0;
 }

 XMLNode_free(doc->nodes[i_node]);
 if (free_node)
  free(doc->nodes[i_node]);

 if (pt != NULL) {
  memcpy(pt,doc->nodes,i_node * sizeof(XMLNode *));
  memcpy(pt + i_node,doc->nodes + i_node + 1,(doc->n_nodes - i_node - 1) * sizeof(XMLNode *));
 }

 if (doc->nodes != NULL)
  free(doc->nodes);
 doc->nodes = pt;
 doc->n_nodes--;

 return 1;
}