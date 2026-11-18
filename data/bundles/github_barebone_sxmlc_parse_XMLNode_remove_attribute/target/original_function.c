int XMLNode_remove_attribute(XMLNode* node, int i_attr)
{
	XMLAttribute* pt;
	if (node == NULL || node->init_value != XML_INIT_DONE || i_attr < 0 || i_attr >= node->n_attributes)
		return -1;

	/* Before modifying first see if we run out of memory */
	if (node->n_attributes == 1)
		pt = NULL;
	else {
		pt = __malloc((node->n_attributes - 1) * sizeof(XMLAttribute));
		if (pt == NULL)
			return -1;
	}

	/* Can't fail anymore, free item */
	if (node->attributes[i_attr].name != NULL) __free(node->attributes[i_attr].name);
	if (node->attributes[i_attr].value != NULL) __free(node->attributes[i_attr].value);

	if (pt != NULL) {
		memcpy(pt, node->attributes, i_attr * sizeof(XMLAttribute));
		memcpy(&pt[i_attr], &node->attributes[i_attr + 1], (node->n_attributes - i_attr - 1) * sizeof(XMLAttribute));
	}
	if (node->attributes != NULL)
		__free(node->attributes);
	node->attributes = pt;
	node->n_attributes--;

	return node->n_attributes;
}