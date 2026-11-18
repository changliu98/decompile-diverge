static int func0(const char *pattern, const char *name, int *mode,
			 int *oid_len)
{
	struct object_id oid;
	struct object *o;
	int ret = -1;

	if (get_oid(pattern, &oid))
		goto out;
	o = parse_object(the_repository, &oid);
	free_object(o);
	if (!o)
		goto out;
	*mode = o->type;
	*oid_len = oid.hash_len;
	ret = 0;
out:
	return ret;
}