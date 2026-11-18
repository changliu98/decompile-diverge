__attribute__((used)) static inline int minor_to_index(dev_t dev)
{
	return dev >> PART_BITS;
}