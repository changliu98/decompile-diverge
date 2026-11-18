int xml_delete_node(struct _XMLDoc *doc, int i_node, int free_node)
{
    if (doc == ((void *)0) || doc->init_value != 427230498 || i_node < 0 || i_node > doc->n_nodes)
        return 0;
    struct _XMLNode **new_nodes = ((void *)0);
    if (doc->n_nodes > 1) {
        new_nodes = (struct _XMLNode **)xml_malloc((doc->n_nodes - 1) * sizeof(struct _XMLNode *));
        if (new_nodes == ((void *)0))
            return 0;
    }
    xml_ref_node(doc->nodes[i_node]);
    if (free_node)
        xml_free_node(doc->nodes[i_node]);
    if (new_nodes != ((void *)0)) {
        xml_copy_array(new_nodes, doc->nodes, i_node * sizeof(struct _XMLNode *));
        xml_copy_array(&new_nodes[i_node], &doc->nodes[i_node + 1], (doc->n_nodes - i_node - 1) * sizeof(struct _XMLNode *));
    }
    if (doc->nodes != ((void *)0))
        xml_free_node(doc->nodes);
    doc->nodes = new_nodes;
    doc->n_nodes--;
    return 1;
}