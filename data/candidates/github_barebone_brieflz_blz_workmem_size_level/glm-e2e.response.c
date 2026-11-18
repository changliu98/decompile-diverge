long blz_workmem_size_level(long arg1, int level) {
    long ret;
    
    // The switch handles levels 1 through 9
    switch (level) {
        case 1:
            ret = blz_lazy_workmem_size(arg1);
            break;
        case 2:
            ret = blz_hashbucket_workmem_size(arg1);
            break;
        case 3:
            ret = blz_leparse_workmem_size(arg1, 2);
            break;
        case 4:
            ret = blz_leparse_workmem_size(arg1, 4);
            break;
        case 5:
            ret = blz_btparse_workmem_size(arg1);
            break;
        case 6:
            ret = blz_pack_level(arg1);
            break;
        default:
            // If level is not between 1 and 9, return -1
            ret = -1;
            break;
    }
    
    return ret;
}