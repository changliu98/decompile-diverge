static RBinRebaseInfo *get_rebase_infos(RBinFile *bf) {
  RBinRebaseInfo *rebase_info = calloc(1, sizeof(RBinRebaseInfo));
  if (!rebase_info) {
    return NULL;
  }
  if (bf->o->rebase_info_offset && bf->o->rebase_info_size) {
    if (bf->o->nb_sections > 1) {
      RBinRebaseInfoEntry *rebase_info_entry =
          calloc(1, sizeof(RBinRebaseInfoEntry));
      if (!rebase_info_entry) {
        free(rebase_info);
        return NULL;
      }
      rebase_info_entry->base = bf->sections[1].vaddr;
      rebase_info_entry->end =
          rebase_info_entry->base + bf->sections[1].vsize;
      rebase_info_entry->next = get_rebase_info(
          bf, bf->o->rebase_info_offset, bf->o->rebase_info_size,
          rebase_info_entry->base, -1);
      rebase_info->entries = rebase_info_entry;
      rebase_info->nb_entries = 1;
      return rebase_info;
    }
  } else {
    unsigned nb_rebase_infos[16];
    unsigned total_nb_rebase_infos = 0;
    unsigned i;
    for (i = 0; i < bf->nb_imports && i < 16; i++) {
      ut64 import_offset = bf->imports[i];
      if (!rz_buf_read_le32_at(bf->buf, import_offset + 0x13c,
                               &nb_rebase_infos[i])) {
        free(rebase_info);
        return NULL;
      }
      total_nb_rebase_infos += nb_rebase_infos[i];
    }
    if (!total_nb_rebase_infos) {
      free(rebase_info);
      return NULL;
    }
    RBinRebaseInfoEntry *rebase_info_entries =
        calloc(total_nb_rebase_infos, sizeof(RBinRebaseInfoEntry));
    if (!rebase_info_entries) {
      free(rebase_info);
      return NULL;
    }
    unsigned nb_rebase_info_entries = 0;
    for (i = 0; i < bf->nb_imports && i < 16; i++) {
      ut64 import_offset = bf->imports[i];
      if (!nb_rebase_infos[i]) {
        continue;
      }
      unsigned j;
      if (!rz_buf_read_le32_at(bf->buf, import_offset + 0x138, &j)) {
        continue;
      }
      ut64 rebase_info_offset = import_offset + j;
      if (!rebase_info_offset) {
        continue;
      }
      RBinRebaseInfoEntry_t rebase_info_entry_t;
      RBinRebaseInfoEntry *prev_rebase_info_entry = NULL;
      for (j = 0; j < nb_rebase_infos[i]; j++) {
        ut64 rebase_info_entry_offset = rebase_info_offset + j * 0x38;
        if (rz_buf_fread_at(bf->buf, rebase_info_entry_offset,
                            (unsigned char *)&rebase_info_entry_t, "6lii",
                            1) != 0x38) {
          break;
        }
        if (!rebase_info_entry_t.rebase_info_offset ||
            !rebase_info_entry_t.rebase_info_size) {
          continue;
        }
        rebase_info_entries[nb_rebase_info_entries].base =
            import_offset + rebase_info_entry_t.rebase_info_base;
        rebase_info_entries[nb_rebase_info_entries].end =
            rebase_info_entries[nb_rebase_info_entries].base +
            rebase_info_entry_t.rebase_info_size;
        rebase_info_entries[nb_rebase_info_entries].next = get_rebase_info(
            bf, import_offset + rebase_info_entry_t.rebase_info_offset,
            rebase_info_entry_t.rebase_info_size,
            import_offset + rebase_info_entry_t.rebase_info_base,
            prev_rebase_info_entry ? prev_rebase_info_entry->base : -1);
        prev_rebase_info_entry =
            rebase_info_entries[nb_rebase_info_entries];
        nb_rebase_info_entries++;
      }
    }
    if (!nb_rebase_info_entries) {
      free(rebase_info_entries);
      free(rebase_info);
      return NULL;
    }
    if (nb_rebase_info_entries < total_nb_rebase_infos) {
      RBinRebaseInfoEntry *new_rebase_info_entries =
          calloc(nb_rebase_info_entries, sizeof(RBinRebaseInfoEntry));
      if (!new_rebase_info_entries) {
        free(rebase_info_entries);
        free(rebase_info);
        return NULL;
      }
      memcpy(new_rebase_info_entries, rebase_info_entries,
             nb_rebase_info_entries * sizeof(RBinRebaseInfoEntry));
      free(rebase_info_entries);
      rebase_info_entries = new_rebase_info_entries;
    }
    rebase_info->entries = rebase_info_entries;
    rebase_info->nb_entries = nb_rebase_info_entries;
    return rebase_info;
  }
  free(rebase_info);
  return NULL;
}