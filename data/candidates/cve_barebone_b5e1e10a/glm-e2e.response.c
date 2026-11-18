void print_udta(void *movie, int track_id, int skip_meta) {
    int udta_count = gf_isom_get_udta_count(movie, track_id);
    
    if (udta_count == 0) {
        return;
    }
    
    if (skip_meta) {
        int i = 0;
        while (i < udta_count) {
            unsigned int udta_type;
            void *udta_data;
            gf_isom_get_udta_type(movie, track_id, i + 1, &udta_type, &udta_data);
            
            if (udta_type == 0x6d657461) { // 'meta'
                udta_count--;
                break;
            }
            i++;
        }
        
        if (udta_count == 0) {
            return;
        }
    }
    
    fprintf(stderr, "Found %d udta\n", udta_count);
    
    for (int i = 0; i < udta_count; i++) {
        int first = 1;
        unsigned int udta_type;
        void *udta_data;
        
        gf_isom_get_udta_type(movie, track_id, i + 1, &udta_type, &udta_data);
        int user_data_count = gf_isom_get_user_data_count(movie, track_id, udta_type, &udta_data);
        
        char *type_str = gf_4cc_to_str(udta_type);
        fprintf(stderr, "\tudta type: %s (%d entries)\n", type_str, user_data_count);
        
        for (int j = 0; j < user_data_count; j++) {
            char *data = NULL;
            int data_len;
            
            gf_isom_get_user_data(movie, track_id, udta_type, &udta_data, j + 1, &data, &data_len);
            
            if (data == NULL) {
                continue;
            }
            
            if (gf_utf8_is_legal(data, data_len)) {
                if (first) {
                    fprintf(stderr, "\n");
                    first = 0;
                }
                fprintf(stderr, "\t\t%s\n", data);
            }
            
            gf_free(data);
        }
    }
    
    fprintf(stderr, "\n");
}