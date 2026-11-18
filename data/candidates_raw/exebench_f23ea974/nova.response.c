static void func0(struct rbsp *rbsp)
{
	u32 tmp = rbsp->data;
	rbsp->data = rbsp->size;
	rbsp->size = tmp;
}