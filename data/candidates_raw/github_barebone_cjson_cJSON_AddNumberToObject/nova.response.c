static struct resource *
func0(struct resource *parent, struct resource *new, size_t size,
		   int flags)
{
	struct resource *conflict;

	new = insert_resource(parent, new, size, flags, &conflict);
	if (new)
		return new;

	release_resource(conflict);
	kfree(conflict);
	return NULL;
}