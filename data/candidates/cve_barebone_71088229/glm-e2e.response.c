Assuming based on context

int read_file_dentry_set(struct exfat_de_iter *iter, struct exfat_inode **new_node, int *dentry_count) {
    struct exfat_dentry *de = NULL;
    struct exfat_dentry *stream_de = NULL;
    struct exfat_dentry *name_de = NULL;
    struct exfat_inode *node = NULL;
    int ret = 0;
    int count = 0;
    uint16_t checksum;
    uint8_t is_corrupted = 0;

    *new_node = NULL;

    ret = exfat_de_iter_get(iter, 0, &de);
    if (ret != 0 || de->type != EXFAT_ENT_TYPE_INVAL) {
        exfat_err("failed to get file dentry set\n");
        return -22; // -EINVAL
    }

    checksum = file_calc_checksum(iter);
    if (checksum != de->checksum) {
        *dentry_count = 1;
        goto skip_corrupted_set;
    }

    if (de->num_ext < 2) {
        *dentry_count = 1;
        goto skip_corrupted_set;
    }

    ret = exfat_de_iter_get(iter, 1, &stream_de);
    if (ret != 0 || stream_de->type != EXFAT_ENT_TYPE_STREAM) {
        *dentry_count = 2;
        goto skip_corrupted_set;
    }

    *new_node = NULL;
    node = exfat_alloc_inode(de->checksum); // checksum is at offset 2, but passed as 32-bit
    if (!node) {
        return -12; // -ENOMEM
    }

    for (count = 2; count <= de->num_ext; count++) {
        ret = exfat_de_iter_get(iter, count, &name_de);
        if (ret != 0 || name_de->type != EXFAT_ENT_TYPE_NAME) {
            if (count > 2 && (count % 2 == 0)) { // This logic seems odd but matches the assembly
                exfat_de_iter_get_dirty(iter, 0, &de);
                de->num_ext = count - 1;
                break;
            } else {
                *dentry_count = count + 1;
                goto skip_corrupted_set;
            }
        }
        
        // Copy name data from name_de to node->name
        // The offsets and calculations match the assembly exactly
        int idx = count - 2;
        uint8_t *src = (uint8_t *)name_de + 2;
        uint8_t *dst = (uint8_t *)node->name + idx * 30;
        
        *(uint64_t *)(dst + 0) = *(uint64_t *)(src + 0);
        *(uint64_t *)(dst + 8) = *(uint64_t *)(src + 8);
        *(uint64_t *)(dst + 16) = *(uint64_t *)(src + 16);
        *(uint32_t *)(dst + 24) = *(uint32_t *)(src + 24);
        *(uint16_t *)(dst + 28) = *(uint16_t *)(src + 28);
    }

    ret = check_name_dentry_set(iter, node);
    if (ret != 0) {
        *dentry_count = de->num_ext + 1;
        goto skip_corrupted_set;
    }

    if (de->num_ext == 2 && stream_de->stream_flags <= 2) {
        ret = handle_dot_dotdot_filename(iter, name_de, stream_de->stream_flags);
        if (ret < 0) {
            *dentry_count = de->num_ext + 1;
            goto skip_corrupted_set;
        }
    }

    node->size = stream_de->data_size; // offset 0x14
    node->is_contiguous = (stream_de->stream_flags & 2) != 0 ? 1 : 0;
    node->start_clu = stream_de->start_clu; // offset 0x18
    node->valid_size = stream_de->valid_size; // offset 0x40

    if (node->valid_size < stream_de->start_clu) { // offset 0x8
        *dentry_count = de->num_ext + 1;
        *dentry_count = de->num_ext + 1; // Duplicate assignment matches assembly
        goto skip_corrupted_set;
    }

    *dentry_count = de->num_ext + 1;
    *new_node = node;
    return 0;

skip_corrupted_set:
    is_corrupted = 1;
    if (is_corrupted) {
        exfat_de_iter_get_dirty(iter, 0, &de);
        de->type &= 0x7f;
    }

    for (count = 1; count < *dentry_count; count++) {
        exfat_de_iter_get(iter, count, &de);
        if (de->type == EXFAT_ENT_TYPE_INVAL) {
            break;
        }
        if (is_corrupted) {
            exfat_de_iter_get_dirty(iter, count, &de);
            de->type &= 0x7f;
        }
        count++;
    }

    *dentry_count = count;
    *new_node = NULL;
    exfat_free_inode(node);
    return is_corrupted ? -1 : -22; // -EIO or -EINVAL
}