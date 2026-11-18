static void bnode_link_set_leaf(struct vio_dring_state *dr)
{
 dr->flags &= ~((1UL << 0));
}