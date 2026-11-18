int GetHintFormat(void* arg) {
    // 0x686d6864 corresponds to the 4-byte ASCII string "dhmh" (or "hmhd" depending on endianness)
    if (*(uint32_t*)arg->ptr1->ptr2->ptr3 != 0x686d6864) {
        return 0;
    }

    struct Item* item = arg->ptr1->ptr2->ptr3;
    
    if (item != NULL && item->field_0x28 != 0) {
        return item->field_0x28;
    }

    struct Item* list_item = gf_list_get(arg->ptr1->ptr2->ptr4->ptr5, 0);

    if (item == NULL) {
        if (list_item != NULL) {
            return list_item->field_0x0;
        } else {
            return 0;
        }
    } else {
        if (list_item != NULL) {
            item->field_0x28 = list_item->field_0x0;
        }
        return item->field_0x28;
    }
}