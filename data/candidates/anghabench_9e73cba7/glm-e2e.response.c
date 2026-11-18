int uasm_in_compat_space_p(int64_t addr) {
    return addr == (int64_t)(int32_t)addr;
}