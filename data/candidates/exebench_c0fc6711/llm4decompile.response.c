void _quadtree_sort_swap(struct quadtree_node *a, struct quadtree_node *b) {
 struct quadtree_node tmp = *a;
 *a = *b;
 *b = tmp;
}