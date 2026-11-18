int __cdecl read_file_dentry_set(exfat_de_iter *iter, exfat_inode **new_node, int *skip_dentries)
{
  exfat_dentry *dentry;
  exfat_dentry *stream_de;
  exfat_dentry *file_de;
  exfat_inode *node = NULL;
  uint16_t checksum;
  int i;

  if (exfat_de_iter_get(iter, 0, &file_de) || file_de->type != EXFAT_FILE)
  {
    exfat_err("failed to get file dentry\n");
    return -EINVAL;
  }

  checksum = file_calc_checksum(iter);
  if (checksum != file_de->dentry.file.secondary_count)
  {
    *skip_dentries = 1;
    goto out;
  }

  if (file_de->dentry.file.secondary_count < 2)
  {
    *skip_dentries = 1;
    goto out;
  }

  if (exfat_de_iter_get(iter, 1, &stream_de) || stream_de->type != EXFAT_STREAM)
  {
    *skip_dentries = 2;
    goto out;
  }

  *new_node = NULL;
  node = exfat_alloc_inode(file_de->dentry.file.secondary_count);
  if (!node)
    return -ENOMEM;

  for (i = 2; i <= file_de->dentry.file.secondary_count; ++i)
  {
    if (exfat_de_iter_get(iter, i, &dentry) || dentry->type != EXFAT_NAME)
    {
      *skip_dentries = i + 1;
      goto out;
    }

    memcpy(&node->name[(i - 2) * 15], dentry->dentry.name.unicode_0_14, 30);
  }

  if (check_name_dentry_set(iter, node))
  {
    *skip_dentries = file_de->dentry.file.secondary_count + 1;
  }
  else if (file_de->dentry.file.secondary_count == 2
           && stream_de->dentry.stream.name_len <= 2
           && handle_dot_dotdot_filename(iter, dentry, stream_de->dentry.stream.name_len) < 0)
  {
    *skip_dentries = file_de->dentry.file.secondary_count + 1;
  }
  else
  {
    node->first_clus = stream_de->dentry.stream.start_clu;
    node->is_contiguous = (stream_de->dentry.stream.flags & EXFAT_SF_CONTIGUOUS) != 0;
    node->size = stream_de->dentry.stream.size;

    if (node->size < stream_de->dentry.stream.valid_size)
    {
      *skip_dentries = file_de->dentry.file.secondary_count + 1;
    }
    else
    {
      *skip_dentries = file_de->dentry.file.secondary_count + 1;
      *new_node = node;
      return 0;
    }
  }

out:
  for (i = 1; i < *skip_dentries; ++i)
  {
    exfat_de_iter_get(iter, i, &dentry);
    if (dentry->type == EXFAT_FILE)
      break;
  }
  *skip_dentries = i;
  *new_node = NULL;
  exfat_free_inode(node);
  return -EINVAL;
}