void file_perms_get(const char *path, int *owner_perms, int *other_perms) {
    struct stat st;

    if (owner_perms != NULL) {
        *owner_perms = 0;
    }

    if (other_perms != NULL) {
        *other_perms = 0;
    }

    if (stat(path, &st) >= 0) {
        if (owner_perms != NULL) {
            *owner_perms = st.st_mode;
        }
        if (other_perms != NULL) {
            *other_perms = st.st_mode & 0xFFF;
        }
    }
}