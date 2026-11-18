static inline void func0(struct rb_node *rb)
{
	rb->__rb_parent_color |= (unsigned long) rb->rb_right & 1;
}