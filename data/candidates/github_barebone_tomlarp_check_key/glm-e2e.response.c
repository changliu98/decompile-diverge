char check_key(struct KeyMap *map, const char *key, char **out_v, char **out_a, char **out_t) {
    char *dummy; // Used as a fallback for NULL out-pointers

    // Fallback for NULL pointers to avoid segmentation faults
    if (!out_t) out_t = &dummy;
    if (!out_a) out_a = &dummy;
    if (!out_v) out_v = &dummy;

    // Initialize out-pointers to NULL
    *out_t = NULL;
    *out_a = NULL;
    *out_v = NULL;

    // Search in v_keys
    for (int i = 0; i < map->v_count; i++) {
        if (strcmp(key, map->v_keys[i]) == 0) {
            *out_v = map->v_keys[i];
            return 'v'; // 0x76
        }
    }

    // Search in a_keys
    for (int i = 0; i < map->a_count; i++) {
        if (strcmp(key, map->a_keys[i]) == 0) {
            *out_a = map->a_keys[i];
            return 'a'; // 0x61
        }
    }

    // Search in t_keys
    for (int i = 0; i < map->t_count; i++) {
        if (strcmp(key, map->t_keys[i]) == 0) {
            *out_t = map->t_keys[i];
            return 't'; // 0x74
        }
    }

    return 0; // 0x0
}