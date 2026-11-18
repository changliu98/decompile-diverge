MOBI_RET mobi_reconstruct_infl(char *outstring, const MOBIIndx *infl, const MOBIIndexEntry *orth_entry) {
    const char *label = orth_entry->label;
    size_t label_length;
    size_t outlen = 0;
    size_t initlen;
    uint32_t *infl_groups = NULL;
    size_t infl_count = mobi_get_indxentry_tagarray(&infl_groups, orth_entry, 42);
    if (infl_count == 0 || infl_groups == NULL) {
        ;
        return MOBI_SUCCESS;
    }
    strcpy(outstring, "<idx:infl>");
    initlen = outlen = strlen("<idx:infl>") + strlen("</idx:infl>");
    label_length = strlen(label);
    if (label_length > 500) {
        ;
        return MOBI_DATA_CORRUPT;
    }
    if (infl->cncx_record == NULL) {
        ;
        return MOBI_DATA_CORRUPT;
    }
    for (size_t i = 0; i < infl_count; i++) {
        size_t offset = infl_groups[i];
        if (offset >= infl->entries_count) {
            ;
            return MOBI_DATA_CORRUPT;
        }
        uint32_t *groups;
        size_t group_count = mobi_get_indxentry_tagarray(&groups, &infl->entries[offset], 5);
        uint32_t *parts;
        size_t part_count = mobi_get_indxentry_tagarray(&parts, &infl->entries[offset], 26);
        if (group_count != part_count) {
            ;
            return MOBI_DATA_CORRUPT;
        }
        for (size_t j = 0; j < part_count; j++) {
            char name_attr[501];
            name_attr[0] = '\0';
            char *group_name = mobi_get_cncx_string(infl->cncx_record, groups[j]);
            if (group_name == NULL) {
                ;
                return MOBI_MALLOC_FAILED;
            }
            if (strlen(group_name) > 0) {
                snprintf(name_attr, 500, " name=\"%s\"", group_name);
            }
            free(group_name);
            char decoded[501];
            memset(decoded, 0, 501);
            unsigned char *rule = (unsigned char *)infl->entries[parts[j]].label;
            memcpy(decoded, label, label_length);
            int decoded_length = (int)label_length;
            MOBI_RET ret = mobi_decode_infl(decoded, &decoded_length, rule);
            if (ret != MOBI_SUCCESS) {
                return ret;
            }
            if (decoded_length == 0) {
                continue;
            }
            char infl_tag[501];
            int written = snprintf(infl_tag, 500, "<idx:iform%s value=\"%s\"/>", name_attr, decoded);
            if (written < 0 || written >= 501) {
                continue;
            }
            outlen += strlen(infl_tag);
            if (outlen > 25000) {
                return MOBI_ERROR;
            }
            strcat(outstring, infl_tag);
        }
    }
    if (outlen == initlen) {
        *outstring = '\0';
    } else {
        strcat(outstring, "</idx:infl>");
    }
    return MOBI_SUCCESS;
}