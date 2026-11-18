int Media_CheckDataEntry(GF_MediaBox *media, uint32_t data_entry_index) {
    int ret;
    GF_DataMap *dm = NULL;
    GF_DataEntry *entry;

    // Check for null pointers and validate index bounds
    if (!media || !data_entry_index) {
        return -1;
    }
    
    // media->minf->dinf->dref->other_boxes (inferred from offsets 0x30, 0x28, 0x28, 0x18)
    void **dref_list = *(void **)((char *)*(void **)((char *)*(void **)((char *)*(void **)((char *)media + 0x30) + 0x28) + 0x28) + 0x18);
    
    if (data_entry_index > (uint32_t)gf_list_count(dref_list)) {
        return -1;
    }

    // Fetch the data entry (1-based index)
    entry = (GF_DataEntry *)gf_list_get(dref_list, data_entry_index - 1);
    if (!entry) {
        return -20; // 0xffffffec
    }

    // If self_contained flag is set, no need to check external references
    if (entry->self_contained == 1) {
        return 0;
    }

    // Check if the entry type is "urn " (0x75726e20)
    if (entry->type == 0x75726e20) {
        return -4; // 0xfffffffc
    }

    // media->minf->dinf->dref
    GF_DataReferenceBox *dref = *(GF_DataReferenceBox **)((char *)*(void **)((char *)*(void **)((char *)media + 0x28) + 0x28) + 0x28);
    
    if (dref->type == 2) {
        // Type 2: Create data map with NULL parent URL
        ret = gf_isom_datamap_new(entry->data_ref, NULL, 1, &dm);
    } else {
        // Other types: Create data map with parent URL from dref
        ret = gf_isom_datamap_new(entry->data_ref, dref->data_ref, 1, &dm);
    }

    if (ret != 0) {
        return ret;
    }

    // Clean up and return success
    gf_isom_datamap_del(dm);
    return 0;
}