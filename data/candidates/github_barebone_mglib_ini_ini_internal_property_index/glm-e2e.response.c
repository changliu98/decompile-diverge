int ini_internal_property_index(struct ini_internal_t *ini, int section_index, int property_index) {
    if (ini != NULL && section_index >= 0 && section_index < ini->section_count) {
        int count = 0;
        for (int i = 0; i < ini->property_count; i++) {
            if (ini->properties[i].section_index == section_index) {
                if (count == property_index) {
                    return i;
                }
                count++;
            }
        }
    }
    return -1;
}