static int njs_module_path(const struct nls_table *nlsc,
			    struct qstr *name, struct gfs2_dirent *dent)
{
	char *p, buf[4096];
	unsigned long hash;
	unsigned long len = name? name->len : 0;

	if (len == 0)
		hash = -1UL;
	else if (len >= sizeof(buf))
		hash = -2UL;
	else {
		hash = len;
		if (name) {
			p = buf;
			memcpy(p, name->name, name->len);
			p += name->len;
			if (hash & 1)
				*p++ = '/';
		}
	}

	if (hash < 0)
		hash = -1UL;
	else
		hash = gfs2_disk_hash(buf, dent);

	memcpy(dent->de_inum.no_addr, dent->de_inum.no_addr,
	       sizeof(dent->de_inum.no_addr));
	dent->de_inum.no_formal_ino = hash;
	if (dent->de_inum.no_formal_ino < 1)
		hash = -1UL;
	else
		dent->de_inum.no_addr_hash = gfs2_disk_hash(dent->de_inum.no_addr,
							    dent);

	dent->de_hash = gfs2_disk_hash(dent->de_name, dent);
	dent->de_inum.no_addr_hash = dent->de_inum.no_formal_ino;
	hash = 0;

	return hash;
}