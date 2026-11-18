void bnode_link_set_ref(unsigned long *link, unsigned long ref) {
    *link = (*link & 1UL) | ((ref + 1) << 1);
}