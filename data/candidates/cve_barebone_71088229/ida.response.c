int __cdecl read_file_dentry_set(exfat_de_iter *iter, exfat_inode **new_node, int *skip_dentries)
{
  __int64 v3; // rcx
  exfat_dentry *v4; // rdx
  uint16_t checksum; // [rsp+4h] [rbp-4Ch]
  int i; // [rsp+Ch] [rbp-44h]
  int ia; // [rsp+Ch] [rbp-44h]
  exfat_inode *node; // [rsp+10h] [rbp-40h]
  exfat_dentry *dentry; // [rsp+18h] [rbp-38h] BYREF
  exfat_dentry *stream_de; // [rsp+20h] [rbp-30h] BYREF
  exfat_dentry *file_de; // [rsp+28h] [rbp-28h] BYREF
  int *skip_dentriesa; // [rsp+30h] [rbp-20h]
  exfat_inode **new_nodea; // [rsp+38h] [rbp-18h]
  exfat_de_iter *itera; // [rsp+40h] [rbp-10h]

  itera = iter;
  new_nodea = new_node;
  skip_dentriesa = skip_dentries;
  node = 0LL;
  if ( !exfat_de_iter_get(iter, 0, &file_de) && file_de->type == 133 )
  {
    checksum = file_calc_checksum(itera);
    if ( checksum == file_de->dentry.vol.volume_label[0] )
    {
      if ( file_de->dentry.vol.character_count >= 2u )
      {
        if ( !exfat_de_iter_get(itera, 1, &stream_de) && stream_de->type == 192 )
        {
          *new_nodea = 0LL;
          node = exfat_alloc_inode(file_de->dentry.vol.volume_label[1]);
          if ( !node )
            return -12;
          for ( i = 2; i <= file_de->dentry.vol.character_count; ++i )
          {
            if ( exfat_de_iter_get(itera, i, &dentry) || dentry->type != 193 )
            {
              *skip_dentriesa = i + 1;
              goto LABEL_28;
            }
            v3 = 15 * (i - 2);
            v4 = dentry;
            *(_QWORD *)&node->name[v3] = *(_QWORD *)dentry->dentry.vol.volume_label;
            *(_QWORD *)&node->name[v3 + 4] = *(_QWORD *)&v4->dentry.guid.guid[4];
            *(_QWORD *)&node->name[v3 + 8] = *(_QWORD *)&v4->dentry.guid.guid[12];
            *(_DWORD *)&node->name[v3 + 12] = *(_DWORD *)&v4->dentry.guid.reserved[4];
            node->name[v3 + 14] = v4->dentry.name.unicode_0_14[14];
          }
          if ( check_name_dentry_set(itera, node) )
          {
            *skip_dentriesa = file_de->dentry.vol.character_count + 1;
          }
          else if ( file_de->dentry.vol.character_count == 2
                 && stream_de->dentry.stream.name_len <= 2u
                 && handle_dot_dotdot_filename(itera, dentry, stream_de->dentry.stream.name_len) < 0 )
          {
            *skip_dentriesa = file_de->dentry.vol.character_count + 1;
          }
          else
          {
            node->first_clus = stream_de->dentry.stream.start_clu;
            node->is_contiguous = (stream_de->dentry.vol.character_count & 2) != 0;
            node->size = stream_de->dentry.stream.size;
            if ( node->size >= stream_de->dentry.stream.valid_size )
            {
              *skip_dentriesa = file_de->dentry.vol.character_count + 1;
              *new_nodea = node;
              return 0;
            }
            *skip_dentriesa = file_de->dentry.vol.character_count + 1;
            *skip_dentriesa = file_de->dentry.vol.character_count + 1;
          }
        }
        else
        {
          *skip_dentriesa = 2;
        }
      }
      else
      {
        *skip_dentriesa = 1;
      }
    }
    else
    {
      *skip_dentriesa = 1;
    }
LABEL_28:
    for ( ia = 1; ia < *skip_dentriesa; ++ia )
    {
      exfat_de_iter_get(itera, ia, &dentry);
      if ( dentry->type == 133 )
        break;
    }
    *skip_dentriesa = ia;
    *new_nodea = 0LL;
    exfat_free_inode(node);
    return -22;
  }
  else
  {
    exfat_err("failed to get file dentry\n");
    return -22;
  }
}