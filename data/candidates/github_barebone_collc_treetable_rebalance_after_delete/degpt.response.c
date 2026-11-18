void rebalance_after_delete(CC_TreeTable *tree, RBNode *node)
{
    RBNode *sibling;
    // Continue rebalancing while x is not the root and x is black (color == 0)
    while (node != tree->root && node->color == '\0') {
        // Case 1: x is a left child
        if (node == node->parent->left) {
            sibling = node->parent->right;
            // Case 1a: Sibling w is red
            if (sibling->color == '\0') {
                sibling->color = '\x01'; // Make w black
                node->parent->color = '\0'; // Make parent red
                rotate_left(tree, node->parent); // Rotate left to make w black
                sibling = node->parent->right; // Update w to new sibling
            }
            // Case 1b: Sibling w is black
            // Case 1b-i: Both of w's children are black
            if (sibling->left->color == '\x01' && sibling->right->color == '\x01') {
                sibling->color = '\0'; // Make w red
                node = node->parent; // Move x up to parent
            } else {
                // Case 1b-ii: w's right child is black, left child is red
                if (sibling->right->color == '\x01') {
                    sibling->left->color = '\x01'; // Make w's left child red
                    sibling->color = '\0'; // Make w black
                    rotate_right(tree, sibling); // Rotate right on w
                    sibling = node->parent->right; // Update w to new sibling
                }
                // Case 1b-iii: w's right child is red
                sibling->color = node->parent->color; // Set w's color to parent's color
                node->parent->color = '\x01'; // Make parent black
                sibling->right->color = '\x01'; // Make w's right child black
                rotate_left(tree, node->parent); // Rotate left on parent
                node = tree->root; // Set x to root to exit loop
            }
        } else {
            // Case 2: x is a right child
            sibling = node->parent->left;
            // Case 2a: Sibling w is red
            if (sibling->color == '\0') {
                sibling->color = '\x01'; // Make w black
                node->parent->color = '\0'; // Make parent red
                rotate_right(tree, node->parent); // Rotate right to make w black
                sibling = node->parent->left; // Update w to new sibling
            }
            // Case 2b: Sibling w is black
            // Case 2b-i: Both of w's children are black
            if (sibling->right->color == '\x01' && sibling->left->color == '\x01') {
                sibling->color = '\0'; // Make w red
                node = node->parent; // Move x up to parent
            } else {
                // Case 2b-ii: w's left child is black, right child is red
                if (sibling->left->color == '\x01') {
                    sibling->right->color = '\x01'; // Make w's right child red
                    sibling->color = '\0'; // Make w black
                    rotate_left(tree, sibling); // Rotate left on w
                    sibling = node->parent->left; // Update w to new sibling
                }
                // Case 2b-iii: w's left child is red
                sibling->color = node->parent->color; // Set w's color to parent's color
                node->parent->color = '\x01'; // Make parent black
                sibling->left->color = '\x01'; // Make w's left child black
                rotate_right(tree, node->parent); // Rotate right on parent
                node = tree->root; // Set x to root to exit loop
            }
        }
    }
    // Set x to black to fix the double-black issue
    node->color = '\x01';
}