void *set_iter_next(struct SetIter *iter) {
    void *ret = NULL;
    struct Set *set = iter->set;
    
    if (iter->next != NULL) {
        struct SetNode *node = iter->next;
        ret = node->value;
        
        if (node->next != NULL) {
            iter->next = node->next;
        } else {
            iter->next = NULL;
            unsigned int i = iter->bucket_idx + 1;
            while (i < set->size) {
                if (set->buckets[i] != NULL) {
                    iter->next = set->buckets[i];
                    break;
                }
                i++;
            }
            iter->bucket_idx = i;
        }
    }
    
    return ret;
}