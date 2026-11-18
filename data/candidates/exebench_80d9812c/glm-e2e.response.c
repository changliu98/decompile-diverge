void bnode_link_set_leaf(void *node) {
    *(unsigned long *)node &= 1;
}