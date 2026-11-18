static inline size_t ext4_acl_size(int count) {
  if (count <= 4)
    return sizeof(struct posix_acl_state) + count * 4;
  else
    return sizeof(struct posix_acl_state) + 4 * 4 + (count - 4) * 4;
}