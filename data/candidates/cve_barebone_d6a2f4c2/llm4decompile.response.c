void
nfs_printfh(netdissect_options *ndo,
	    const u_char *fhp, u_int len)
{
	my_fsid fsid;
	u_long ino;
	char *sfsname = NULL;
	const u_char *cp;
	const char *sep;
	u_int i;

	if (ndo->ndo_uflag) {
		/*
		 * Print the raw file handle.
		 */
		sep = "";
		(*ndo->ndo_printf)(ndo, " fh[");
		for (cp = fhp, i = 0; i < len; i++, cp++) {
			(*ndo->ndo_printf)(ndo, "%s%x", sep, *cp);
			sep = ":";
		}
		(*ndo->ndo_printf)(ndo, "]");
		return;
	}

	/*
	 * Try to parse the file handle.
	 */
	Parse_fh(fhp, len, &fsid, &ino, NULL, &sfsname, NULL);
	if (sfsname) {
		/*
		 * We got a filesystem name, so we don't need to
		 * print the filesystem number.
		 */
		(void)strncpy(tempstr, sfsname, 64);
		tempstr[64] = '\0';
		cp = strchr(tempstr, ' ');
		if (cp)
			*cp = '\0';
		(*ndo->ndo_printf)(ndo, " fh %s/", tempstr);
	} else {
		/*
		 * Print the filesystem number.
		 */
		(*ndo->ndo_printf)(ndo, " fh %d,%d/",
			    fsid.Fsid_dev.Major, fsid.Fsid_dev.Minor);
	}
	if (fsid.Fsid_dev.Minor == 257) {
		/*
		 * Sun NFS.
		 */
		(*ndo->ndo_printf)(ndo, "%s", fsid.Opaque_Handle);
	} else {
		/*
		 * Traditional NFS.
		 */
		(*ndo->ndo_printf)(ndo, "%ld", ino);
	}
}