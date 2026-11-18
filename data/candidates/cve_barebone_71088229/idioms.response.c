int read_file_dentry_set(struct exfat_de_iter *iter, struct exfat_inode **new_node, int *skip_dentries)
{
  struct exfat_dentry *de;
  struct exfat_dentry *file_de;
  struct exfat_dentry *stream_de;
  struct exfat_inode *node = ((void *)0);
  int i;
  unsigned short checksum;
  if (exfat_de_iter_get(iter, 0, &de)) {
    exfat_de_iter_put(de);
    return -22;
  }
  if (de->type != EXFAT_TYPE_FILE) {
    exfat_de_iter_put(de);
    return -22;
  }
  checksum = exfat_de_iter_get_checksum(iter);
  if (checksum != de->dentry.vol.volume_label[0]) {
    *skip_dentries = 1;
    for (i = 1; i < *skip_dentries; i++) {
      exfat_de_iter_get(iter, i, &de);
      if (de->type == EXFAT_TYPE_DIR)
        break;
    }
    *skip_dentries = i;
    *new_node = ((void *)0);
    exfat_inode_put(node);
    return -22;
  }
  if (de->dentry.vol.character_count < 2) {
    *skip_dentries = 1;
    goto out;
  }
  if (exfat_de_iter_get(iter, 1, &de)) {
    exfat_de_iter_put(de);
    *skip_dentries = 2;
    goto out;
  }
  if (de->type != EXFAT_TYPE_STREAM) {
    exfat_de_iter_put(de);
    *skip_dentries = 2;
    goto out;
  }
  *new_node = ((void *)0);
  node = exfat_inode_get(de->dentry.vol.volume_label[1]);
  if (!node)
    return -12;
  for (i = 2; i <= de->dentry.vol.character_count; i++) {
    if (exfat_de_iter_get(iter, i, &de)) {
      *skip_dentries = i + 1;
      break;
    }
    if (de->type != EXFAT_TYPE_FILE)
      continue;
    memcpy(&node->name[15 * (i - 2)], de->dentry.vol.volume_label,
           sizeof(de->dentry.vol.volume_label));
  }
  if (exfat_de_iter_get_next(iter, node)) {
    *skip_dentries = de->dentry.vol.character_count + 1;
    goto out;
  }
  if (de->dentry.vol.character_count == 2 &&
      de->dentry.stream.name_len <= 2 &&
      exfat_de_iter_get_name(iter, de, de->dentry.stream.name_len) < 0) {
    *skip_dentries = de->dentry.vol.character_count + 1;
    goto out;
  }
  node->first_clus = de->dentry.stream.start_clu;
  node->is_contiguous = de->dentry.vol.character_count & 2;
  node->size = de->dentry.stream.size;
  if (node->size < de->dentry.stream.valid_size) {
    *skip_dentries = de->dentry.vol.character_count + 1;
    *skip_dentries = de->dentry.vol.character_count + 1;
    goto out;
  }
  *skip_dentries = de->dentry.vol.character_count + 1;
  *new_node = node;
  out:
  for (i = 1; i < *skip_dentries; i++) {
    exfat_de_iter_get(iter, i, &de);
    if (de->type == EXFAT_TYPE_DIR)
      break;
  }
  *skip_dentries = i;
  *new_node = ((void *)0);
  exfat_inode_put(node);
  return -22;
}