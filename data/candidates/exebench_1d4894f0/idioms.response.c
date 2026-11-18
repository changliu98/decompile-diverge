static inline void stack4_replace_top(struct itree_node *node, unsigned long end)
{
 node->start = (node->start & ~0xf) | end;
}