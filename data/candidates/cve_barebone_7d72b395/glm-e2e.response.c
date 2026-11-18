int read_new_config_info(struct config_info *cfg, struct config_input *input) {
    int remaining = input->length;
    char *ptr = input->data;
    int i;
    int size;
    int ret = 0;

    cfg->field_58 = 1;
    cfg->field_68 = 0;
    cfg->field_10 = 0;
    cfg->field_5c = 0;

    if (cfg->field_60 != NULL) {
        free(cfg->field_60);
        cfg->field_60 = NULL;
    }

    if (remaining != 0) {
        cfg->field_5c = *ptr++;
        cfg->field_10 = (cfg->field_10 & 0xffffff00) | (*ptr++);
        remaining -= 2;

        if (remaining != 0) {
            cfg->field_68 = (*ptr++) << 10;
            remaining--;

            if (remaining != 0) {
                size = *ptr++;
                cfg->field_68 += size;
                remaining--;

                if (remaining < size) {
                    return 0;
                }

                cfg->field_60 = malloc(size);
                if (cfg->field_60 != NULL) {
                    for (i = 0; i < size; i++) {
                        if (remaining != 0) {
                            cfg->field_60[i] = *ptr++;
                            remaining--;
                        } else {
                            cfg->field_60[i] = (char)i;
                        }
                    }
                }
            } else {
                cfg->field_68 += cfg->field_10;
            }
        }
    }

    return 1;
}