int __cdecl XMLDoc_remove_node(XMLDoc *doc, int i_node, int free_node)
{
  XMLNode **pt; // [rsp+0h] [rbp-20h]

  if ( !doc || doc->init_value != 427230498 || i_node < 0 || i_node > doc->n_nodes )
    return 0;
  if ( doc->n_nodes == 1 )
  {
    pt = 0LL;
  }
  else
  {
    pt = (XMLNode **)malloc(8LL * (doc->n_nodes - 1));
    if ( !pt )
      return 0;
  }
  XMLNode_free(doc->nodes[i_node]);
  if ( free_node )
    free(doc->nodes[i_node]);
  if ( pt )
  {
    memcpy(pt, &doc->nodes[i_node], 8LL * i_node);
    memcpy(&pt[i_node], &doc->nodes[i_node + 1], 8LL * (doc->n_nodes - i_node - 1));
  }
  if ( doc->nodes )
    free(doc->nodes);
  doc->nodes = pt;
  --doc->n_nodes;
  return 1;
}