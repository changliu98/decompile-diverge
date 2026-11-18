int XMLDoc_remove_node(XMLDoc* doc, int index, int free_node)
{
 int ret;
 XMLNode** tmp;

 if (!((doc) != NULL && (doc)->init_value == 0x19770522) || index < 0 || index > doc->n_nodes)
  return(0);

 if (doc->n_nodes == 1) {
  tmp = NULL;
 } else {
  tmp = (XMLNode**) malloc((doc->n_nodes - 1) * sizeof(XMLNode*));
  if (tmp == NULL)
   return(0);
 }

 XMLNode_free(doc->nodes[index]);
 if (free_node)
  free(doc->nodes[index]);

 if (tmp != NULL) {
  memcpy(tmp, doc->nodes, index * sizeof(XMLNode*));
  memcpy(tmp + index, doc->nodes + index + 1,
         (doc->n_nodes - index - 1) * sizeof(XMLNode*));
 }

 if (doc->nodes != NULL)
  free(doc->nodes);

 doc->nodes = tmp;
 doc->n_nodes--;

 return(1);
}