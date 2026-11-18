char * nfs_error_string(int status)

{
  int status_local;
  char *local_10;
  
  switch(status) {
  case 0x80:
    local_10 = "NFS4_OK";
    break;
  case 0x81:
    local_10 = "NFS4ERR_XDEV";
    break;
  case 0x82:
    local_10 = "NFS4ERR_WRONG_TYPE";
    break;
  case 0x83:
    local_10 = "NFS4ERR_WRONG_CRED";
    break;
  case 0x84:
    local_10 = "NFS4ERR_WRONGSEC";
    break;
  case 0x85:
    local_10 = "NFS4ERR_UNSAFE_COMPOUND";
    break;
  case 0x86:
    local_10 = "NFS4ERR_UNKNOWN_LAYOUTTYPE";
    break;
  case 0x87:
    local_10 = "NFS4ERR_TOO_MANY_OPS";
    break;
  case 0x88:
    local_10 = "NFS4ERR_TOOSMALL";
    break;
  case 0x89:
    local_10 = "NFS4ERR_SYMLINK";
    break;
  case 0x8a:
    local_10 = "NFS4ERR_STALE_STATEID";
    break;
  case 0x8b:
    local_10 = "NFS4ERR_STALE_CLIENTID";
    break;
  case 0x8c:
    local_10 = "NFS4ERR_STALE";
    break;
  case 0x8d:
    local_10 = "NFS4ERR_SHARE_DENIED";
    break;
  case 0x8e:
    local_10 = "NFS4ERR_SERVERFAULT";
    break;
  case 0x8f:
    local_10 = "NFS4ERR_SEQ_MISORDERED";
    break;
  case 0x90:
    local_10 = "NFS4ERR_SEQ_FALSE_RETRY";
    break;
  case 0x91:
    local_10 = "NFS4ERR_SEQUENCE_POS";
    break;
  case 0x92:
    local_10 = "NFS4ERR_SAME";
    break;
  case 0x93:
    local_10 = "NFS4ERR_ROFS";
    break;
  case 0x94:
    local_10 = "NFS4ERR_RETURNCONFLICT";
    break;
  case 0x95:
    local_10 = "NFS4ERR_RETRY_UNCACHED_REP";
    break;
  case 0x96:
    local_10 = "NFS4ERR_RESTOREFH";
    break;
  case 0x97:
    local_10 = "NFS4ERR_RESOURCE";
    break;
  case 0x98:
    local_10 = "NFS4ERR_REQ_TOO_BIG";
    break;
  case 0x99:
    local_10 = "NFS4ERR_REP_TOO_BIG_TO_CACHE";
    break;
  case 0x9a:
    local_10 = "NFS4ERR_REP_TOO_BIG";
    break;
  case 0x9b:
    local_10 = "NFS4ERR_REJECT_DELEG";
    break;
  case 0x9c:
    local_10 = "NFS4ERR_RECLAIM_CONFLICT";
    break;
  case 0x9d:
    local_10 = "NFS4ERR_RECLAIM_BAD";
    break;
  case 0x9e:
    local_10 = "NFS4ERR_RECALLCONFLICT";
    break;
  case 0x9f:
    local_10 = "NFS4ERR_PNFS_NO_LAYOUT";
    break;
  case 0xa0:
    local_10 = "NFS4ERR_PNFS_IO_HOLE";
    break;
  case 0xa1:
    local_10 = "NFS4ERR_PERM";
    break;
  case 0xa2:
    local_10 = "NFS4ERR_OP_NOT_IN_SESSION";
    break;
  case 0xa3:
    local_10 = "NFS4ERR_OP_ILLEGAL";
    break;
  case 0xa4:
    local_10 = "NFS4ERR_OPENMODE";
    break;
  case 0xa5:
    local_10 = "NFS4ERR_OLD_STATEID";
    break;
  case 0xa6:
    local_10 = "NFS4ERR_NXIO";
    break;
  case 0xa7:
    local_10 = "NFS4ERR_NO_GRACE";
    break;
  case 0xa8:
    local_10 = "NFS4ERR_NOT_SAME";
    break;
  case 0xa9:
    local_10 = "NFS4ERR_NOT_ONLY_OP";
    break;
  case 0xaa:
    local_10 = "NFS4ERR_NOTSUPP";
    break;
  case 0xab:
    local_10 = "NFS4ERR_NOTEMPTY";
    break;
  case 0xac:
    local_10 = "NFS4ERR_NOTDIR";
    break;
  case 0xad:
    local_10 = "NFS4ERR_NOSPC";
    break;
  case 0xae:
    local_10 = "NFS4ERR_NOMATCHING_LAYOUT";
    break;
  case 0xaf:
    local_10 = "NFS4ERR_NOFILEHANDLE";
    break;
  case 0xb0:
    local_10 = "NFS4ERR_NOENT";
    break;
  case 0xb1:
    local_10 = "NFS4ERR_NAMETOOLONG";
    break;
  case 0xb2:
    local_10 = "NFS4ERR_MOVED";
    break;
  case 0xb3:
    local_10 = "NFS4ERR_MLINK";
    break;
  case 0xb4:
    local_10 = "NFS4ERR_MINOR_VERS_MISMATCH";
    break;
  case 0xb5:
    local_10 = "NFS4ERR_LOCK_RANGE";
    break;
  case 0xb6:
    local_10 = "NFS4ERR_LOCK_NOTSUPP";
    break;
  case 0xb7:
    local_10 = "NFS4ERR_LOCKS_HELD";
    break;
  case 0xb8:
    local_10 = "NFS4ERR_LOCKED";
    break;
  case 0xb9:
    local_10 = "NFS4ERR_LEASE_MOVED";
    break;
  case 0xba:
    local_10 = "NFS4ERR_LAYOUTUNAVAILABLE";
    break;
  case 0xbb:
    local_10 = "NFS4ERR_LAYOUTTRYLATER";
    break;
  case 0xbc:
    local_10 = "NFS4ERR_ISDIR";
    break;
  case 0xbd:
    local_10 = "NFS4ERR_IO";
    break;
  case 0xbe:
    local_10 = "NFS4ERR_INVAL";
    break;
  case 0xbf:
    local_10 = "NFS4ERR_HASH_ALG_UNSUPP";
    break;
  case 0xc0:
    local_10 = "NFS4ERR_GRACE";
    break;
  case 0xc1:
    local_10 = "NFS4ERR_FILE_OPEN";
    break;
  case 0xc2:
    local_10 = "NFS4ERR_FHEXPIRED";
    break;
  case 0xc3:
    local_10 = "NFS4ERR_FBIG";
    break;
  case 0xc4:
    local_10 = "NFS4ERR_EXPIRED";
    break;
  case 0xc5:
    local_10 = "NFS4ERR_EXIST";
    break;
  case 0xc6:
    local_10 = "NFS4ERR_ENCR_ALG_UNSUPP";
    break;
  case 199:
    local_10 = "NFS4ERR_DQUOT";
    break;
  case 200:
    local_10 = "NFS4ERR_DIRDELEG_UNAVAIL";
    break;
  case 0xc9:
    local_10 = "NFS4ERR_DENIED";
    break;
  case 0xca:
    local_10 = "NFS4ERR_DELEG_REVOKED";
    break;
  case 0xcb:
    local_10 = "NFS4ERR_DELEG_ALREADY_WANTED";
    break;
  case 0xcc:
    local_10 = "NFS4ERR_DELAY";
    break;
  case 0xcd:
    local_10 = "NFS4ERR_DEADSESSION";
    break;
  case 0xce:
    local_10 = "NFS4ERR_DEADLOCK";
    break;
  case 0xcf:
    local_10 = "NFS4ERR_CONN_NOT_BOUND_TO_SESSION";
    break;
  case 0xd0:
    local_10 = "NFS4ERR_COMPLETE_ALREADY";
    break;
  case 0xd1:
    local_10 = "NFS4ERR_CLIENTID_BUSY";
    break;
  case 0xd2:
    local_10 = "NFS4ERR_CLID_INUSE";
    break;
  case 0xd3:
    local_10 = "NFS4ERR_CB_PATH_DOWN";
    break;
  case 0xd4:
    local_10 = "NFS4ERR_BAD_STATEID";
    break;
  case 0xd5:
    local_10 = "NFS4ERR_BAD_SESSION_DIGEST";
    break;
  case 0xd6:
    local_10 = "NFS4ERR_BAD_SEQID";
    break;
  case 0xd7:
    local_10 = "NFS4ERR_BAD_RANGE";
    break;
  case 0xd8:
    local_10 = "NFS4ERR_BAD_HIGH_SLOT";
    break;
  case 0xd9:
    local_10 = "NFS4ERR_BAD_COOKIE";
    break;
  case 0xda:
    local_10 = "NFS4ERR_BADXDR";
    break;
  case 0xdb:
    local_10 = "NFS4ERR_BADTYPE";
    break;
  case 0xdc:
    local_10 = "NFS4ERR_BADSLOT";
    break;
  case 0xdd:
    local_10 = "NFS4ERR_BADSESSION";
    break;
  case 0xde:
    local_10 = "NFS4ERR_BADOWNER";
    break;
  case 0xdf:
    local_10 = "NFS4ERR_BADNAME";
    break;
  case 0xe0:
    local_10 = "NFS4ERR_BADLAYOUT";
    break;
  case 0xe1:
    local_10 = "NFS4ERR_BADIOMODE";
    break;
  case 0xe2:
    local_10 = "NFS4ERR_BADHANDLE";
    break;
  case 0xe3:
    local_10 = "NFS4ERR_BADCHAR";
    break;
  case 0xe4:
    local_10 = "NFS4ERR_BACK_CHAN_BUSY";
    break;
  case 0xe5:
    local_10 = "NFS4ERR_ATTRNOTSUPP";
    break;
  case 0xe6:
    local_10 = "NFS4ERR_ADMIN_REVOKED";
    break;
  case 0xe7:
    local_10 = "NFS4ERR_ACCESS";
    break;
  default:
    local_10 = "invalid nfs error code";
  }
  return local_10;
}