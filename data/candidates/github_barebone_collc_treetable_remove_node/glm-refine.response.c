void __cdecl remove_node(CC_TreeTable *table, RBNode *z)
{
  RBNode *replacement; // Replaces 'y'
  RBNode *fixup_node;  // Replaces 'x'
  int deleted_color;   // Replaces 'y_color'

  deleted_color = z->color;

  // Case 1 & 2: z has at most one non-sentinel child
  if (z->left == table->sentinel)
  {
    fixup_node = z->right;
    transplant(table, z, fixup_node);
  }
  else if (z->right == table->sentinel)
  {
    fixup_node = z->left;
    transplant(table, z, fixup_node);
  }
  // Case 3: z has two non-sentinel children
  else
  {
    // Find the minimum node in z's right subtree
    replacement = tree_min(table, z->right);
    deleted_color = replacement->color;
    fixup_node = replacement->right;

    // If the minimum is the direct right child of z
    if (replacement->parent == z)
    {
      fixup_node->parent = replacement;
    }
    // If the minimum is deeper in the subtree
    else
    {
      transplant(table, replacement, replacement->right);
      replacement->right = z->right;
      replacement->right->parent = replacement;
    }

    transplant(table, z, replacement);
    replacement->left = z->left;
    replacement->left->parent = replacement;
    replacement->color = z->color;
  }

  // A black node was removed, violating the Red-Black tree properties
  if (deleted_color == 1)
  {
    rebalance_after_delete(table, fixup_node);
  }

  // Free the memory of the removed node and update the table size
  table->mem_free(z);
  --table->size;
}