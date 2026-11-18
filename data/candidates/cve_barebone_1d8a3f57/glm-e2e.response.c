int stszin(int arg) {
    u32in(); // Skip 1st u32 (version & flags)
    u32in(); // Skip 2nd u32 (sample size)
    
    mp4config.field_30 = u32in(); // sample_count
    
    mp4config.field_28 = malloc((mp4config.field_30 + 1) * 4);
    
    if (mp4config.field_28 == NULL) {
        return -1;
    }
    
    int sum = 0;
    mp4config.field_28[0] = 0;
    
    for (unsigned int i = 0; i < mp4config.field_30; i++) {
        unsigned int sample_size = u32in();
        sum += sample_size;
        
        if (mp4config.field_38 < sample_size) {
            mp4config.field_38 = sample_size;
        }
        
        mp4config.field_28[i + 1] = sum;
        
        if (sum < mp4config.field_28[i]) {
            return -1;
        }
    }
    
    return arg;
}