int read_new_config_info(struct ConfigInfo *cfg, struct ConfigData *src) {
    int remaining = src->length;
    char *ptr = src->data;
    int i;
    int chunk_size;
    int result;

    cfg->field_58 = 1;
    cfg->field_70 = 0;
    cfg->field_10 = 0;
    cfg->field_5c = 0;

    if (cfg->field_60 != NULL) {
        free(cfg->field_60);
        cfg->field_60 = NULL;
    }

    if (remaining != 0) {
        cfg->field_5c = *ptr++;
        cfg->field_10 = (cfg->field_10 & 0xFFFFFF00) | *ptr++;
        remaining -= 2;

        if (remaining != 0) {
            cfg->field_70 = (*ptr++) << 10;
            remaining--;

            if (remaining != 0) {
                chunk_size = *ptr++;
                cfg->field_70 += chunk_size;
                remaining--;

                if (remaining < chunk_size) {
                    return 0;
                }

                cfg->field_60 = malloc(chunk_size);
                if (cfg->field_60 != NULL) {
                    for (i = 0; i < chunk_size; i++) {
                        if (remaining != 0) {
                            cfg->field_60[i] = *ptr++;
                            remaining--;
                        } else {
                            cfg->field_60[i] = (char)i;
                        }
                    }
                }
            } else {
                cfg->field_70 += cfg->field_74; // field_74 is at offset 0x1c
            }
        }
    }

    return 1;
}