/* WARNING: Removing unreachable block (ram,0x0010156d) */
/* WARNING: Removing unreachable block (ram,0x00101790) */
/* WARNING: Removing unreachable block (ram,0x0010172b) */
/* WARNING: Removing unreachable block (ram,0x001017ef) */

int read_file_dentry_set(exfat_de_iter *iter,exfat_inode **new_node,int *skip_dentries)

{
  uint16_t uVar1;
  int iVar2;
  long lVar3;
  uint16_t checksum;
  _Bool need_delete;
  int ret;
  int i;
  exfat_inode *node;
  exfat_dentry *dentry;
  exfat_dentry *stream_de;
  exfat_dentry *file_de;
  int *skip_dentries_local;
  exfat_inode **new_node_local;
  exfat_de_iter *iter_local;
  
  node = (exfat_inode *)0x0;
  skip_dentries_local = skip_dentries;
  new_node_local = new_node;
  iter_local = iter;
  iVar2 = exfat_de_iter_get(iter,0,&file_de);
  if ((iVar2 != 0) || (file_de->type != 0x85)) {
    exfat_err("failed to get file dentry\n");
    return -0x16;
  }
  uVar1 = file_calc_checksum(iter_local);
  if (uVar1 == (file_de->dentry).vol.volume_label[0]) {
    if ((file_de->dentry).vol.character_count < 2) {
      *skip_dentries_local = 1;
    }
    else {
      iVar2 = exfat_de_iter_get(iter_local,1,&stream_de);
      if ((iVar2 == 0) && (stream_de->type == 0xc0)) {
        *new_node_local = (exfat_inode *)0x0;
        node = exfat_alloc_inode((file_de->dentry).guid.flags);
        if (node == (exfat_inode *)0x0) {
          return -0xc;
        }
        for (i = 2; i <= (int)(uint)(file_de->dentry).vol.character_count; i = i + 1) {
          iVar2 = exfat_de_iter_get(iter_local,i,&dentry);
          if ((iVar2 != 0) || (dentry->type != 0xc1)) {
            *skip_dentries_local = i + 1;
            goto LAB_00101721;
          }
          lVar3 = (long)((i + -2) * 0xf);
          *(undefined8 *)((long)&node[1].parent + lVar3 * 2) =
               *(undefined8 *)((long)&dentry->dentry + 1);
          *(undefined8 *)((long)&node[1].children.next + lVar3 * 2) =
               *(undefined8 *)((long)&(dentry->dentry).stream.valid_size + 2);
          *(undefined8 *)((long)&node[1].children.prev + lVar3 * 2) =
               *(undefined8 *)((long)&dentry->dentry + 0x11);
          *(undefined4 *)((long)&node[1].sibling.next + lVar3 * 2) =
               *(undefined4 *)((long)&dentry->dentry + 0x19);
          *(__le16 *)((long)&node[1].sibling.next + lVar3 * 2 + 4) =
               (dentry->dentry).name.unicode_0_14[0xe];
        }
        iVar2 = check_name_dentry_set(iter_local,node);
        if (iVar2 == 0) {
          if ((((file_de->dentry).vol.character_count == '\x02') &&
              ((stream_de->dentry).stream.name_len < 3)) &&
             (iVar2 = handle_dot_dotdot_filename
                                (iter_local,dentry,(uint)(stream_de->dentry).stream.name_len),
             iVar2 < 0)) {
            *skip_dentries_local = (file_de->dentry).vol.character_count + 1;
          }
          else {
            node->first_clus = (stream_de->dentry).stream.start_clu;
            node->is_contiguous = ((stream_de->dentry).vol.character_count & 2) != 0;
            node->size = (stream_de->dentry).stream.size;
            if ((stream_de->dentry).stream.valid_size <= node->size) {
              *skip_dentries_local = (file_de->dentry).vol.character_count + 1;
              *new_node_local = node;
              return 0;
            }
            *skip_dentries_local = (file_de->dentry).vol.character_count + 1;
            *skip_dentries_local = (file_de->dentry).vol.character_count + 1;
          }
        }
        else {
          *skip_dentries_local = (file_de->dentry).vol.character_count + 1;
        }
      }
      else {
        *skip_dentries_local = 2;
      }
    }
  }
  else {
    *skip_dentries_local = 1;
  }
LAB_00101721:
  i = 1;
  while ((i < *skip_dentries_local &&
         (exfat_de_iter_get(iter_local,i,&dentry), dentry->type != 0x85))) {
    i = i + 1;
  }
  *skip_dentries_local = i;
  *new_node_local = (exfat_inode *)0x0;
  exfat_free_inode(node);
  return -0x16;
}