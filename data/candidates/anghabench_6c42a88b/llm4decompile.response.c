size_t ext4_acl_size(int count)
{
	size_t size;

	if (count <= 4)
		size = sizeof(struct ext4_acl_entry) +
		       count * sizeof(struct ext4_acl_entry_short);
	else
		size = sizeof(struct ext4_acl_entry) +
		       4 * sizeof(struct ext4_acl_entry_short) +
		       (count - 4) * sizeof(struct ext4_acl_entry);
	return size;
}