bool subtree_is_valid(struct Tree* tree, int index) {
    // Check left child (index * 2)
    if ((long)(index * 2) < tree->size) {
        void* parent_val = tree->get_value(tree, index);
        void* left_val = tree->get_value(tree, index * 2);
        
        if (tree->compare(parent_val, left_val)) {
            return false;
        }
        
        if (!subtree_is_valid(tree, index * 2)) {
            return false;
        }
    }
    
    // Check right child (index * 2 + 1)
    if ((long)(index * 2 + 1) < tree->size) {
        void* parent_val = tree->get_value(tree, index);
        void* right_val = tree->get_value(tree, index * 2 + 1);
        
        if (tree->compare(parent_val, right_val)) {
            return false;
        }
        
        if (!subtree_is_valid(tree, index * 2 + 1)) {
            return false;
        }
    }
    
    return true;
}