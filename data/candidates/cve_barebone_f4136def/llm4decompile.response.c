smb_sdrc_t
smb_com_flush(smb_request_t *sr)
{
	smb_sdrc_t status;

	if (!smb_flush_required) {
		if (!smbsr_encode_empty_result(sr))
			return (0);
		return (1);
	}
	if (sr->smb_fid == 0xffff) {
		smb_llist_t *ll = &sr->tid_tree->t_ofile_list;
		smb_ofile_t *ofile;

		smb_llist_enter(ll, RW_READER);
		for (ofile = smb_llist_head(ll); ofile != NULL;
		    ofile = smb_llist_next(ll, ofile)) {
			mutex_enter(&ofile->f_mutex);
			smb_flush_file(sr, ofile);
			mutex_exit(&ofile->f_mutex);
		}
		smb_llist_exit(ll);
	} else {
		smbsr_lookup_file(sr);
		if (sr->fid_ofile == NULL) {
			smbsr_status(sr, 0xC0000008, 1, 6);
			return (SDRC_ERROR);
		}
		smb_flush_file(sr, sr->fid_ofile);
	}
	if (!smbsr_encode_empty_result(sr))
		return (0);
	return (1);
}