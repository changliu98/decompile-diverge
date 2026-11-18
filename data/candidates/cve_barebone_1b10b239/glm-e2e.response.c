int read_new_config_info(struct ConfigInfo *cfg, struct ConfigData *cfg_data) {
    int remaining = cfg_data->length;
    char *ptr = cfg_data->data;

    cfg->field_6c = 1;
    cfg->field_88 = 0;
    cfg->field_10 = 0;
    cfg->field_70 = 0;

    if (cfg->field_78 != NULL) {
        free(cfg->field_78);
        cfg->field_78 = NULL;
    }

    if (remaining != 0) {
        cfg->field_70 = *ptr++;
        cfg->field_10 = (cfg->field_10 & 0xFFFFFF00) | (*ptr++ & 0xFF);
        remaining -= 2;

        if (remaining != 0) {
            cfg->field_88 = (*ptr++ << 16);
            remaining--;

            if (remaining != 0) {
                int alloc_size = *ptr++;
                cfg->field_88 += alloc_size;
                remaining--;

                if (remaining < alloc_size) {
                    return 0;
                }

                cfg->field_78 = malloc(alloc_size);
                if (cfg->field_78 != NULL) {
                    for (int i = 0; i < alloc_size; i++) {
                        if (remaining != 0) {
                            ((char *)cfg->field_78)[i] = *ptr++;
                            remaining--;
                        } else {
                            ((char *)cfg->field_78)[i] = (char)i;
                        }
                    }
                }
            } else {
                cfg->field_88 += cfg->field_1c;
            }
        }
    }

    return 1;
}