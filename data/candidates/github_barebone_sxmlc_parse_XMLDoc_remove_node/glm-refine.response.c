define XML_DOC_INIT_MAGIC 0x19740422

bool XMLDoc_remove_node(XMLDoc *doc, size_t i_node, bool free_node)
{
    XMLNode **new_nodes;

    // Validate document, magic number, and node index bounds
    if (!doc || doc->init_value != XML_DOC_INIT_MAGIC || i_node > doc->n_nodes)
        return false;

    // Allocate a new array for the nodes, shrinking it by 1.
    // If there's only 1 node left, the new array will be NULL.
    if (doc->n_nodes == 1)
    {
        new_nodes = NULL;
    }
    else
    {
        new_nodes = (XMLNode **)malloc(sizeof(XMLNode *) * (doc->n_nodes - 1));
        if (!new_nodes)
            return false;
    }

    // Clean up the target node's internal data, and optionally free the object itself
    XMLNode_free(doc->nodes[i_node]);
    if (free_node)
        free(doc->nodes[i_node]);

    // Copy the remaining nodes over to the new array:
    // 1. Copy all nodes before the removed index
    // 2. Copy all nodes after the removed index
    if (new_nodes)
    {
        memcpy(new_nodes, &doc->nodes[i_node], sizeof(XMLNode *) * i_node);
        memcpy(&new_nodes[i_node], &doc->nodes[i_node + 1], sizeof(XMLNode *) * (doc->n_nodes - i_node - 1));
    }

    // Free the old nodes array and update the document
    if (doc->nodes)
        free(doc->nodes);

    doc->nodes = new_nodes;
    doc->n_nodes--;

    return true;
}