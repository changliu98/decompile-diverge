int read_file_dentry_set(exfat_de_iter *iter,
  exfat_inode **new_node, int *skip_dentries)
{
 int i, err;
 uint16_t checksum;
 exfat_inode *node = NULL;
 exfat_dentry *file_de, *stream_de, *dentry;

 err = exfat_de_iter_get(iter, 0, (struct dentry **)&file_de);
 if (err || file_de->type != 0x85) {
  exfat_err("failed to get file dentry\n");
  goto error;
 }

 checksum = file_calc_checksum(iter);
 if (checksum != file_de->dentry.file.checksum) {
  *skip_dentries = 1;
  goto skip_dentries;
 }

 if (file_de->dentry.file.dentry_count < 2) {
  *skip_dentries = 1;
  goto skip_dentries;
 }

 err = exfat_de_iter_get(iter, 1, (struct dentry **)&stream_de);
 if (err || stream_de->type != 0xC0) {
  *skip_dentries = 2;
  goto skip_dentries;
 }

 *new_node = NULL;
 node = exfat_alloc_inode(file_de->dentry.file.type);
 if (!node) {
  err = -12;
  goto out;
 }

 for (i = 2; i <= file_de->dentry.file.dentry_count; i++) {
  err = exfat_de_iter_get(iter, i, (struct dentry **)&dentry);
  if (err || dentry->type != 0xC1) {
   *skip_dentries = i + 1;
   goto skip_dentries;
  }

  node[i - 2].first_clus = dentry->dentry.stream.start_clu;
  node[i - 2].size = dentry->dentry.stream.size;
  node[i - 2].valid_size = dentry->dentry.stream.valid_size;
  node[i - 2].name_len = dentry->dentry.stream.name_len;
  node[i - 2].name_hash = dentry->dentry.stream.name_hash;
 }

 err = check_name_dentry_set(iter, node);
 if (err) {
  *skip_dentries = file_de->dentry.file.dentry_count + 1;
  goto skip_dentries;
 }

 if (file_de->dentry.file.dentry_count == 2 &&
  stream_de->dentry.stream.name_len <= 2) {
  err = handle_dot_dotdot_filename(iter, dentry,
   stream_de->dentry.stream.name_len);
  if (err < 0) {
   *skip_dentries = file_de->dentry.file.dentry_count + 1;
   goto skip_dentries;
  }
 }

 node->first_clus = stream_de->dentry.stream.start_clu;
 node->is_contiguous =
  (stream_de->dentry.stream.name_len & 0x02) ? true : false;
 node->size = stream_de->dentry.stream.size;

 if (node->size < stream_de->dentry.stream.valid_size) {
  *skip_dentries = file_de->dentry.file.dentry_count + 1;
  goto error;
 }

 *skip_dentries = file_de->dentry.file.dentry_count + 1;
 *new_node = node;
 return 0;

skip_dentries:
 for (i = 1; i < *skip_dentries; i++) {
  exfat_de_iter_get(iter, i, (struct dentry **)&dentry);
  if (dentry->type == 0x85)
   break;
 }
 *skip_dentries = i;
 *new_node = NULL;
 exfat_free_inode(node);
error:
 return -22;
out:
 return err;
}