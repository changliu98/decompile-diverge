size_t ext4_acl_size(int entry_count)
{
  // Calculate the size of the ACL structure based on the number of entries.
  // If count is less than 5, the size is count * 4 + 4.
  // Otherwise, the size is (count - 4) * 4 + 0x14.
  return entry_count < 5 ? (size_t)entry_count * 4 + 4 : (size_t)(entry_count - 4) * 4 + 0x14;
}