/* WARNING: Enum "_BOM_TYPE": Some values do not have unique names */

int XMLDoc_remove_node(XMLDoc *doc,int i_node,int free_node)

{
  XMLNode **pt;
  int free_node_local;
  int i_node_local;
  XMLDoc *doc_local;
  int local_c;
  
  if ((((doc == (XMLDoc *)0x0) || (doc->init_value != 0x19770522)) || (i_node < 0)) ||
     (doc->n_nodes < i_node)) {
    local_c = 0;
  }
  else {
    if (doc->n_nodes == 1) {
      pt = (XMLNode **)0x0;
    }
    else {
      pt = malloc((long)(doc->n_nodes + -1) << 3);
      if (pt == (XMLNode **)0x0) {
        return 0;
      }
    }
    XMLNode_free(doc->nodes[i_node]);
    if (free_node != 0) {
      free(doc->nodes[i_node]);
    }
    if (pt != (XMLNode **)0x0) {
      memcpy(pt,doc->nodes + i_node,(long)i_node << 3);
      memcpy(pt + i_node,doc->nodes + (i_node + 1),(long)((doc->n_nodes - i_node) + -1) << 3);
    }
    if (doc->nodes != (XMLNode **)0x0) {
      free(doc->nodes);
    }
    doc->nodes = pt;
    doc->n_nodes = doc->n_nodes + -1;
    local_c = 1;
  }
  return local_c;
}