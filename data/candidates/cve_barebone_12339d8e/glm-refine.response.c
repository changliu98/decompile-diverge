define MAX_OUT_LEN 0x61A8

MOBI_RET __cdecl mobi_reconstruct_infl(char *outstring, const MOBIIndx *infl, const MOBIIndexEntry *orth_entry)
{
    const char *label = orth_entry->label;
    uint32_t *infl_groups = NULL;
    
    // Retrieve inflection groups. If none exist or retrieval fails, return success.
    size_t infl_count = mobi_get_indxentry_tagarray(&infl_groups, orth_entry, 0x2A);
    if (!infl_count || !infl_groups)
        return MOBI_SUCCESS;

    const char *start_tag = "<idx:infl>";
    const char *end_tag = "</idx:infl>";
    const char *iform_tag = "<idx:iform%s value=\"%s\"/>";

    // Initialize outstring with the start tag
    strcpy(outstring, start_tag);
    
    size_t initlen = strlen(start_tag) + strlen(end_tag);
    size_t outlen = initlen;
    size_t label_length = strlen(label);

    // Validate label length and cncx_record presence
    if (label_length > MAX_INFL_LEN)
        return MOBI_DATA_CORRUPT;
    if (!infl->cncx_record)
        return MOBI_DATA_CORRUPT;

    // Iterate over each inflection group
    for (size_t i = 0; i < infl_count; ++i)
    {
        size_t offset = infl_groups[i];
        if (offset >= infl->entries_count)
            return MOBI_DATA_CORRUPT;

        uint32_t *groups = NULL;
        uint32_t *parts = NULL;
        
        size_t group_cnt = mobi_get_indxentry_tagarray(&groups, &infl->entries[offset], 5);
        size_t part_cnt = mobi_get_indxentry_tagarray(&parts, &infl->entries[offset], 0x1A);

        if (group_cnt != part_cnt)
            return MOBI_DATA_CORRUPT;

        // Iterate over each part in the group
        for (size_t j = 0; j < part_cnt; ++j)
        {
            char name_attr[MAX_INFL_LEN + 1] = {0};
            
            char *group_name = mobi_get_cncx_string(infl->cncx_record, groups[j]);
            if (!group_name)
                return MOBI_MALLOC_FAILED;

            if (strlen(group_name))
                snprintf(name_attr, MAX_INFL_LEN, " name=\"%s\"", group_name);
            free(group_name);

            unsigned char decoded[MAX_INFL_LEN + 1] = {0};
            unsigned char *rule = (unsigned char *)infl->entries[parts[j]].label;
            
            memcpy(decoded, label, label_length);
            int decoded_length = label_length;
            
            MOBI_RET ret = mobi_decode_infl(decoded, &decoded_length, rule);
            if (ret)
                return ret;

            if (decoded_length)
            {
                char infl_tag[MAX_INFL_LEN + 1];
                int tag_len = snprintf(infl_tag, MAX_INFL_LEN, iform_tag, name_attr, decoded);
                
                if (tag_len <= MAX_INFL_LEN)
                {
                    outlen += strlen(infl_tag);
                    if (outlen > MAX_OUT_LEN)
                        return MOBI_BUFFER_OVERFLOW;
                    
                    strcat(outstring, infl_tag);
                }
            }
        }
    }

    // Finalize the outstring
    if (outlen == initlen)
        outstring[0] = '\0';
    else
        strcat(outstring, end_tag);

    return MOBI_SUCCESS;
}