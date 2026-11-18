/*
 * Converts an NFSv4 error status code to its corresponding human-readable string.
 *
 * @param status The NFSv4 error status code (e.g., 0x80, 0x81, etc.)
 * @return A pointer to a static string representing the error name,
 *         or "invalid nfs error code" if the status is unrecognized.
 */
char * nfs_error_string(int error_code)
{
  switch(error_code) {
  case 0x80: return "NFS4_OK";
  case 0x81: return "NFS4ERR_XDEV";
  case 0x82: return "NFS4ERR_WRONG_TYPE";
  case 0x83: return "NFS4ERR_WRONG_CRED";
  case 0x84: return "NFS4ERR_WRONGSEC";
  case 0x85: return "NFS4ERR_UNSAFE_COMPOUND";
  case 0x86: return "NFS4ERR_UNKNOWN_LAYOUTTYPE";
  case 0x87: return "NFS4ERR_TOO_MANY_OPS";
  case 0x88: return "NFS4ERR_TOOSMALL";
  case 0x89: return "NFS4ERR_SYMLINK";
  case 0x8a: return "NFS4ERR_STALE_STATEID";
  case 0x8b: return "NFS4ERR_STALE_CLIENTID";
  case 0x8c: return "NFS4ERR_STALE";
  case 0x8d: return "NFS4ERR_SHARE_DENIED";
  case 0x8e: return "NFS4ERR_SERVERFAULT";
  case 0x8f: return "NFS4ERR_SEQ_MISORDERED";
  case 0x90: return "NFS4ERR_SEQ_FALSE_RETRY";
  case 0x91: return "NFS4ERR_SEQUENCE_POS";
  case 0x92: return "NFS4ERR_SAME";
  case 0x93: return "NFS4ERR_ROFS";
  case 0x94: return "NFS4ERR_RETURNCONFLICT";
  case 0x95: return "NFS4ERR_RETRY_UNCACHED_REP";
  case 0x96: return "NFS4ERR_RESTOREFH";
  case 0x97: return "NFS4ERR_RESOURCE";
  case 0x98: return "NFS4ERR_REQ_TOO_BIG";
  case 0x99: return "NFS4ERR_REP_TOO_BIG_TO_CACHE";
  case 0x9a: return "NFS4ERR_REP_TOO_BIG";
  case 0x9b: return "NFS4ERR_REJECT_DELEG";
  case 0x9c: return "NFS4ERR_RECLAIM_CONFLICT";
  case 0x9d: return "NFS4ERR_RECLAIM_BAD";
  case 0x9e: return "NFS4ERR_RECALLCONFLICT";
  case 0x9f: return "NFS4ERR_PNFS_NO_LAYOUT";
  case 0xa0: return "NFS4ERR_PNFS_IO_HOLE";
  case 0xa1: return "NFS4ERR_PERM";
  case 0xa2: return "NFS4ERR_OP_NOT_IN_SESSION";
  case 0xa3: return "NFS4ERR_OP_ILLEGAL";
  case 0xa4: return "NFS4ERR_OPENMODE";
  case 0xa5: return "NFS4ERR_OLD_STATEID";
  case 0xa6: return "NFS4ERR_NXIO";
  case 0xa7: return "NFS4ERR_NO_GRACE";
  case 0xa8: return "NFS4ERR_NOT_SAME";
  case 0xa9: return "NFS4ERR_NOT_ONLY_OP";
  case 0xaa: return "NFS4ERR_NOTSUPP";
  case 0xab: return "NFS4ERR_NOTEMPTY";
  case 0xac: return "NFS4ERR_NOTDIR";
  case 0xad: return "NFS4ERR_NOSPC";
  case 0xae: return "NFS4ERR_NOMATCHING_LAYOUT";
  case 0xaf: return "NFS4ERR_NOFILEHANDLE";
  case 0xb0: return "NFS4ERR_NOENT";
  case 0xb1: return "NFS4ERR_NAMETOOLONG";
  case 0xb2: return "NFS4ERR_MOVED";
  case 0xb3: return "NFS4ERR_MLINK";
  case 0xb4: return "NFS4ERR_MINOR_VERS_MISMATCH";
  case 0xb5: return "NFS4ERR_LOCK_RANGE";
  case 0xb6: return "NFS4ERR_LOCK_NOTSUPP";
  case 0xb7: return "NFS4ERR_LOCKS_HELD";
  case 0xb8: return "NFS4ERR_LOCKED";
  case 0xb9: return "NFS4ERR_LEASE_MOVED";
  case 0xba: return "NFS4ERR_LAYOUTUNAVAILABLE";
  case 0xbb: return "NFS4ERR_LAYOUTTRYLATER";
  case 0xbc: return "NFS4ERR_ISDIR";
  case 0xbd: return "NFS4ERR_IO";
  case 0xbe: return "NFS4ERR_INVAL";
  case 0xbf: return "NFS4ERR_HASH_ALG_UNSUPP";
  case 0xc0: return "NFS4ERR_GRACE";
  case 0xc1: return "NFS4ERR_FILE_OPEN";
  case 0xc2: return "NFS4ERR_FHEXPIRED";
  case 0xc3: return "NFS4ERR_FBIG";
  case 0xc4: return "NFS4ERR_EXPIRED";
  case 0xc5: return "NFS4ERR_EXIST";
  case 0xc6: return "NFS4ERR_ENCR_ALG_UNSUPP";
  case 199: return "NFS4ERR_DQUOT";
  case 200: return "NFS4ERR_DIRDELEG_UNAVAIL";
  case 0xc9: return "NFS4ERR_DENIED";
  case 0xca: return "NFS4ERR_DELEG_REVOKED";
  case 0xcb: return "NFS4ERR_DELEG_ALREADY_WANTED";
  case 0xcc: return "NFS4ERR_DELAY";
  case 0xcd: return "NFS4ERR_DEADSESSION";
  case 0xce: return "NFS4ERR_DEADLOCK";
  case 0xcf: return "NFS4ERR_CONN_NOT_BOUND_TO_SESSION";
  case 0xd0: return "NFS4ERR_COMPLETE_ALREADY";
  case 0xd1: return "NFS4ERR_CLIENTID_BUSY";
  case 0xd2: return "NFS4ERR_CLID_INUSE";
  case 0xd3: return "NFS4ERR_CB_PATH_DOWN";
  case 0xd4: return "NFS4ERR_BAD_STATEID";
  case 0xd5: return "NFS4ERR_BAD_SESSION_DIGEST";
  case 0xd6: return "NFS4ERR_BAD_SEQID";
  case 0xd7: return "NFS4ERR_BAD_RANGE";
  case 0xd8: return "NFS4ERR_BAD_HIGH_SLOT";
  case 0xd9: return "NFS4ERR_BAD_COOKIE";
  case 0xda: return "NFS4ERR_BADXDR";
  case 0xdb: return "NFS4ERR_BADTYPE";
  case 0xdc: return "NFS4ERR_BADSLOT";
  case 0xdd: return "NFS4ERR_BADSESSION";
  case 0xde: return "NFS4ERR_BADOWNER";
  case 0xdf: return "NFS4ERR_BADNAME";
  case 0xe0: return "NFS4ERR_BADLAYOUT";
  case 0xe1: return "NFS4ERR_BADIOMODE";
  case 0xe2: return "NFS4ERR_BADHANDLE";
  case 0xe3: return "NFS4ERR_BADCHAR";
  case 0xe4: return "NFS4ERR_BACK_CHAN_BUSY";
  case 0xe5: return "NFS4ERR_ATTRNOTSUPP";
  case 0xe6: return "NFS4ERR_ADMIN_REVOKED";
  case 0xe7: return "NFS4ERR_ACCESS";
  default: return "invalid nfs error code";
  }
}