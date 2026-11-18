static __inline char *func0(const char *fname)
{
	static char path[9 + 1 + 20 + 1];	
	char *p;
	int error;

	strncpy(path, fname, 9);
	error = device_get_nameunit(path, path, sizeof(path) - 1, NULL, 0);
	p = (error == 0)? " (SCSI)" : " (SCSITape)";
	strcat(path, p);
	return path;
}