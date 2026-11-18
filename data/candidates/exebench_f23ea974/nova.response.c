static void array_are_reference_type(struct rbsp *rbsp)
{
	u32 tmp = rbsp->data;
	rbsp->data = rbsp->size;
	rbsp->size = tmp;
}