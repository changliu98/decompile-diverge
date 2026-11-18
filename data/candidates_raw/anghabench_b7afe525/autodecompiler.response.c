__attribute__((used)) static inline int add_idx(int idx, int inc)
{
	return (idx + 1) & (inc - 1);
}