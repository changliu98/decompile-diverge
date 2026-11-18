__attribute__((used)) static inline int MAJOR(dev_t dev)
{
	return dev >> PART_BITS;
}