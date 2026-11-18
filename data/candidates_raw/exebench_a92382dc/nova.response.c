static int
func0(device_t dev, device_t child, int type, int rid,
    struct bhnd_resource *r)
{
	
	r->direct = false;
	r->res = NULL;

	return (0);
}