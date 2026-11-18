static struct mntarg *
AcquireBilateralTLS(u_int n, struct mntarg *ma, struct mntaarg *mna)
{
	struct mntarg *nma;
	u_int i;

	nma = malloc(sizeof(struct mntarg) * (n + 1), M_MOUNT, M_WAITOK);
	if (nma == NULL)
		return (NULL);
	memset(nma, 0, sizeof(struct mntarg) * n);
	for (i = 0; i < n; i++) {
		nma[i] = mount_arg(ma, mna + i);
		if (nma[i].value == NULL) {
			free(nma, M_MOUNT);
			return (NULL);
		}
	}
	return (nma);
}