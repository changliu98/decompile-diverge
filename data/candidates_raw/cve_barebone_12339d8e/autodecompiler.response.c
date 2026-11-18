static int mobi_build_infl(char *tag, MOBICNCX *cncx, MOBIXMLTag *orth) {
    char *orth_value = orth->value;
    unsigned int infl_groups[10] = {0};
    size_t infl_count = mobi_get_indxentry_tagarray(infl_groups, orth, 42);
    if (infl_count == 0 || !infl_groups) {
        ;
        return (0);
    }
    char *start_tag = "<idx:infl>";
    char *end_tag = "</idx:infl>";
    char *iform_tag = "<idx:iform%s value=\"%s\"/>";
    strcpy(tag, start_tag);
    size_t outlen = strlen(start_tag) + strlen(end_tag);
    size_t initlen = outlen;
    size_t label_length = strlen(orth_value);
    if (label_length > 500) {
        ;
        return (3);
    }
    if (!cncx->infls) {
        ;
        return (3);
    }
    size_t i;
    for (i = 0; i < infl_count; i++) {
        size_t group_index = infl_groups[i];
        if (group_index >= cncx->infl_group_count) {
            ;
            return (3);
        }
        unsigned int groups[10];
        size_t group_cnt = mobi_get_indxentry_tagarray(groups, &cncx->infls[group_index], 5);
        unsigned int parts[10];
        size_t part_cnt = mobi_get_indxentry_tagarray(parts, &cncx->infls[group_index], 26);
        if (group_cnt != part_cnt) {
            ;
            return (3);
        }
        size_t j;
        for (j = 0; j < part_cnt; j++) {
            char name_attr[500] = {0};
            char *group_name = mobi_get_cncx_string(cncx->infls, groups[j]);
            if (!group_name) {
                ;
                return (7);
            }
            if (strlen(group_name)) {
                snprintf(name_attr, 500, " name=\"%s\"", group_name);
            }
            free(group_name);
            char infl[500 +1] = {0};
            char *rule = cncx->infls[parts[j]].value;
            memcpy(infl, orth_value, label_length);
            size_t infl_length = label_length;
            int ret = mobi_decode_infl(infl, &infl_length, rule);
            if (ret) {
                ;
                return (ret);
            }
            if (infl_length == 0) {
                continue;
            }
            char infl_tag[500];
            int len = snprintf(infl_tag, 500, iform_tag, name_attr, infl);
            if (len > 500) {
                ;
                continue;
            }
            outlen += strlen(infl_tag);
            if (outlen > 25000) {
                ;
                return (1);
            }
            strcat(tag, infl_tag);
        }
    }
    if (outlen == initlen) {
        tag[0] = '\0';
    } else {
        strcat(tag, end_tag);
    }
    return (0);
}