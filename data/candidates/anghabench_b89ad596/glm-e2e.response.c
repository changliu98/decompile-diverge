uint32_t xfs_cui_log_format_sizeof(uint32_t nextents) {
    return (nextents * 4) + 4;
}