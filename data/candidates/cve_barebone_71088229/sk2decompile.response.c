static int read_file_dentry_set(struct exfat_de_iter *iter,
                                struct exfat_inode **inode, int *end) {
  struct exfat_inode *ret = NULL;
  struct de *file_dentry, *parent_dentry, *cur_dentry;
  unsigned short checksum;
  int i, j;
  if (exfat_de_iter_get(iter, 0, &file_dentry) || file_dentry->type != 0x85) {
    exfat_err("failed to get file dentry\n");
    return -22;
  }
  checksum = file_calc_checksum(iter);
  if (checksum != file_dentry->u.file.checksum) {
    *end = 1;
    goto out;
  }
  if (file_dentry->u.file.n_entry < 2) {
    *end = 1;
    goto out;
  }
  if (exfat_de_iter_get(iter, 1, &parent_dentry) ||
      parent_dentry->type != 0xc0) {
    *end = 2;
    goto out;
  }
  *inode = NULL;
  ret = exfat_alloc_inode(file_dentry->u.file.start_clu);
  if (!ret) return -12;
  for (i = 2; i <= file_dentry->u.file.n_entry; i++) {
    if (exfat_de_iter_get(iter, i, &cur_dentry) || cur_dentry->type != 0xc1) {
      *end = i + 1;
      goto out;
    }
    for (j = 0; j < 15; j++)
      ret->entry[i - 2].name[j] = cur_dentry->u.dir.name[j];
  }
  if (check_name_dentry_set(iter, ret)) {
    *end = file_dentry->u.file.n_entry + 1;
    goto out;
  }
  if (file_dentry->u.file.n_entry == 2 &&
      parent_dentry->u.dir_ent.n_sub_entry < 3) {
    if (handle_dot_dotdot_filename(iter, cur_dentry,
                                   parent_dentry->u.dir_ent.n_sub_entry) < 0) {
      *end = file_dentry->u.file.n_entry + 1;
      goto out;
    }
  } else {
    ret->parent_clu = parent_dentry->u.dir_ent.clu;
    ret->is_dir = parent_dentry->u.file.n_entry & 0x02;
    ret->size = parent_dentry->u.dir_ent.file_size;
    if (ret->size < parent_dentry->u.dir_ent.start_offset) {
      *end = file_dentry->u.file.n_entry + 1;
      *end = file_dentry->u.file.n_entry + 1;
      goto out;
    }
  }
  *end = file_dentry->u.file.n_entry + 1;
  *inode = ret;
  return 0;
out:
  for (i = 1; i < *end; i++) {
    exfat_de_iter_get(iter, i, &cur_dentry);
    if (cur_dentry->type == 0x85) break;
  }
  *end = i;
  *inode = NULL;
  exfat_free_inode(ret);
  return -22;
}