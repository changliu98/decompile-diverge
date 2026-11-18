define BLACK 1

void __cdecl rebalance_after_delete(CC_TreeTable *table, RBNode *x)
{
    // Continue looping as long as x is not the root and x is BLACK
    while (x != table->root && x->color == BLACK)
    {
        RBNode *parent = x->parent;
        
        if (x == parent->left)
        {
            RBNode *w = parent->right;
            
            // Case 1: x's sibling w is red
            if (w->color == RED)
            {
                w->color = BLACK;
                parent->color = RED;
                rotate_left(table, parent);
                w = parent->right;
            }
            
            // Case 2: Both of w's children are black
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = parent;
            }
            else
            {
                // Case 3: w's right child is black (left child must be red)
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotate_right(table, w);
                    w = parent->right;
                }
                
                // Case 4: w's right child is red
                w->color = parent->color;
                parent->color = BLACK;
                w->right->color = BLACK;
                rotate_left(table, parent);
                
                x = table->root;
            }
        }
        else // x == parent->right (Mirror of the above logic)
        {
            RBNode *w = parent->left;
            
            // Case 1: x's sibling w is red
            if (w->color == RED)
            {
                w->color = BLACK;
                parent->color = RED;
                rotate_right(table, parent);
                w = parent->left;
            }
            
            // Case 2: Both of w's children are black
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = parent;
            }
            else
            {
                // Case 3: w's left child is black (right child must be red)
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotate_left(table, w);
                    w = parent->left;
                }
                
                // Case 4: w's left child is red
                w->color = parent->color;
                parent->color = BLACK;
                w->left->color = BLACK;
                rotate_right(table, parent);
                
                x = table->root;
            }
        }
    }
    
    // Ensure the final node is black
    x->color = BLACK;
}