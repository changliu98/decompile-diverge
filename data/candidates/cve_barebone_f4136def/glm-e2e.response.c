define NT_STATUS_INVALID_HANDLE 0xC0000008

int smb_com_flush(struct smb_request *sr) {
    int ret = 0;
    int encode_result;

    if (smb_flush_required == 0) {
        encode_result = smbsr_encode_empty_result(sr);
        ret = (encode_result == 0) ? 1 : 0;
        return ret;
    }

    if (sr->fid != 0xFFFF) {
        smbsr_lookup_file(sr);
        if (sr->ofile == NULL) {
            smbsr_status(sr, NT_STATUS_INVALID_HANDLE, 1, 6);
            return 1;
        }
        smb_flush_file(sr, sr->ofile);
    } else {
        void *llist = sr->llist;
        smb_llist_enter(llist, 0);
        void *ofile = smb_llist_head(llist);
        
        while (ofile != NULL) {
            mutex_enter(ofile);
            smb_flush_file(sr, ofile);
            mutex_exit(ofile);
            ofile = smb_llist_next(llist, ofile);
        }
        smb_llist_exit(llist);
    }

    encode_result = smbsr_encode_empty_result(sr);
    ret = (encode_result == 0) ? 1 : 0;
    return ret;
}