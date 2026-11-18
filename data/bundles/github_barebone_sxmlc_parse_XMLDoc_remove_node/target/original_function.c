int XMLDoc_remove_node(XMLDoc* doc, int i_node, int free_node)
{
	XMLNode** pt;
	if (doc == NULL || doc->init_value != XML_INIT_DONE || i_node < 0 || i_node > doc->n_nodes)
		return FALSE;

	/* Before modifying first see if we run out of memory */
	if (doc->n_nodes == 1)
		pt = NULL;
	else {
		pt = __malloc((doc->n_nodes - 1) * sizeof(XMLNode*));
		if (pt == NULL)
			return FALSE;
	}

	/* Can't fail anymore, free item */
	(void)XMLNode_free(doc->nodes[i_node]);
	if (free_node) __free(doc->nodes[i_node]);

	if (pt != NULL) {
		memcpy(pt, &doc->nodes[i_node], i_node * sizeof(XMLNode*));
		memcpy(&pt[i_node], &doc->nodes[i_node + 1], (doc->n_nodes - i_node - 1) * sizeof(XMLNode*));
	}

	if (doc->nodes != NULL)
		__free(doc->nodes);
	doc->nodes = pt;
	doc->n_nodes--;

	return TRUE;
}