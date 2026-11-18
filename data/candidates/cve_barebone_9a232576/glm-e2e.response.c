void *parse_die(void *ptr, void *end, struct S1 *arg2, void *arg3, struct S2 *arg4, void *arg5, void *arg6, int arg7) {
    long i;
    char *name = NULL;
    long key = -1;
    char *new_name;

    for (i = 0; i < arg2->field20; i++) {
        memset(arg4->field30 + i * 0x28, 0, 0x28);
        
        ptr = parse_attr_value(
            ptr,
            (int)(end - ptr),
            arg2,
            arg2->field30 + i * 0x18,
            arg4->field30 + i * 0x28,
            arg3,
            arg5,
            arg6,
            arg7
        );
        
        struct S3 *attr = arg4->field30 + i * 0x28;
        
        if (attr->field0 == 0x1b && (attr->field8 == 0xe || attr->field8 == 0x8) && attr->field18 != 0) {
            name = attr->field18;
        }
        
        if (attr->field0 == 0x10) {
            if (attr->field10 == 2) {
                key = attr->field18;
            } else if (attr->field10 == 9) {
                key = attr->field18;
            }
        }
        
        arg4->field10++;
    }
    
    if (name != NULL && key != -1) {
        new_name = strdup(name);
        if (new_name != NULL) {
            if (!ht_up_insert(arg2->field20, key, new_name)) {
                free(new_name);
            }
        }
    }
    
    return ptr;
}