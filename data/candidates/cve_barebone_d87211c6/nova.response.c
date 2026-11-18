struct Node *rb_xml_reader_attribute_hash(struct Node *root) {
    struct Node *ptr = root;
    struct Node *ptr1 = root;
    if (isleaf(ptr) == 0) {
        ptr1 = ptr;
    } else {
        struct Node *ptr2 = leftmost(ptr);
        struct Node *sibling;
        struct Node *parent = NULL;
        struct Node *grandchild = NULL;
        sibling = ptr2->right;
        while (sibling == NULL) {
            parent = findparent(ptr2);
            grandchild = findgrandchild(ptr2);
            if (grandchild!= NULL) {
                sibling = findsibling(grandchild);
            }
            rotateleft(parent, sibling);
            ptr2 = ptr2->left;
        }
        ptr1 = ptr2;
    }
    return ptr1;
}