static inline void bnode_link_set_leaf(struct rb_node *rb)
{
	rb->__rb_parent_color |= (unsigned long) rb->rb_right & 1;
}