static const char *func0(const char *sym_name) {
    struct kld_file_stat file;
    struct kld_stat stat;
    const char *result;

    if (kldfindfile(sym_name, &file, 1) == 0) {
        if (kldstat(file.id, &stat, 1, &file, 0) == 0) {
            kldunload(file.id);
            result = "unload";
        } else {
            result = "unload (kldstat)";
        }
    } else {
        result = "load";
    }
    return result;
}