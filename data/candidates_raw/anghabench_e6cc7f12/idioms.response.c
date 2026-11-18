static inline int rcache_index(int hash)
{
 return (hash + (sizeof(struct rcache_entry) * (sizeof(int) * 8) - 1)) / (sizeof(int) * 8) * (sizeof(int) * 8);
}