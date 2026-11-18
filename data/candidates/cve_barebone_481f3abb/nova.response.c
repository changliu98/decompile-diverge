int xf_rail_server_execute_result(struct node *root, struct node *temp) {
    assert(root!= NULL);
    assert(temp!= NULL);
    assert(root->parent!= NULL);

    if (temp->color == RED) {
        assert(root->parent->parent!= NULL);
        assert(root->parent->parent->parent!= NULL);
        assert(root->parent->parent->parent->parent!= NULL);
    }

    if (temp->parent!= NULL) {
        memcpy(&(temp->left), &(nodes[temp->parent->left]), sizeof(struct node *));
        memcpy(&(temp->right), &(nodes[temp->parent->right]), sizeof(struct node *));
    } else {
        memcpy(&(temp->left), &(nodes[0]), sizeof(struct node *));
        memcpy(&(temp->right), &(nodes[0]), sizeof(struct node *));
    }

    return 0;
}