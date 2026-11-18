int wacom_intuos_id_mangle(int id) {
    return ((id & 0xfffff000) << 4) | (id & 0xfff);
}