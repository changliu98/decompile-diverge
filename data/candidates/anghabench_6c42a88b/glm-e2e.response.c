int64_t ext4_acl_size(int count) {
    int64_t size;
    
    if (count <= 4) {
        size = ((int64_t)count << 2) + 4;
    } else {
        size = ((int64_t)(count - 4) << 2) + 20;
    }
    
    return size;
}