static inline void set_end(struct itree_node *node, unsigned long end)
{
 node->start = (node->start & ~0xf) | end;
}