static char *mfile_name_concat(const char *path, const char *name, char **parent) {
	size_t path_len = strlen(path);
	size_t name_len = strlen(name);
	size_t len = path_len + name_len;
	char *parent_path = NULL;
	char *file_path = NULL;
	char sep = (path_len > 0 && (path[path_len - 1]!= '/' && name[0]!= '/'))? '/' : '\0';

	if ((file_path = (char *) malloc(len + 1)) == NULL) {
		return NULL;
	}

	strncpy(file_path, path, path_len);
	char *p = file_path + path_len;
	*p++ = sep;
	if (sep!= '\0') {
		if (parent!= NULL) {
			*parent = p;
		}
	}
	strncpy(p, name, name_len);
	p += name_len;
	*p = '\0';

	parent_path = file_path;
	if (parent!= NULL) {
		*parent = file_path + path_len;
	}

	return parent_path;
}