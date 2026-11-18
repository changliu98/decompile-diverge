static struct mdesc_handle *func0(unsigned short type,
					     unsigned char nb,
					     unsigned char op)
{
	struct mdesc_elem *e;
	struct mdesc_handle *hp;
	unsigned long off;

	if (nb < 1 || nb > 15 || op > 4 || op > nb)
		return NULL;

	off = (type + (1 << op) + nb - 1) * sizeof(*e);

	e = (struct mdesc_elem *)(mdesc_mem_virt + off);
	hp = mdesc_handle_get(e);
	if (!hp)
		return NULL;

	hp->mdesc = e;
	hp->op = op;
	hp->nb = nb;

	mdesc_get(hp);

	return hp;
}