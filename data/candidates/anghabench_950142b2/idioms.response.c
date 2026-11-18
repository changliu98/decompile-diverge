char *nfs_error_string(int err)
{
  char *errstr = ((void *)0);
  switch (err) {
  case (int)NFS4ERR_OK:
    errstr = "NFS4_OK";
    break;
  case (int)NFS4ERR_XDEV:
    errstr = "NFS4ERR_XDEV";
    break;
  case (int)NFS4ERR_WRONG_TYPE:
    errstr = "NFS4ERR_WRONG_TYPE";
    break;
  case (int)NFS4ERR_WRONG_CRED:
    errstr = "NFS4ERR_WRONG_CRED";
    break;
  case (int)NFS4ERR_WRONGSEC:
    errstr = "NFS4ERR_WRONGSEC";
    break;
  case (int)NFS4ERR_UNSAFE_COMPOUND:
    errstr = "NFS4ERR_UNSAFE_COMPOUND";
    break;
  case (int)NFS4ERR_UNKNOWN_LAYOUTTYPE:
    errstr = "NFS4ERR_UNKNOWN_LAYOUTTYPE";
    break;
  case (int)NFS4ERR_TOO_MANY_OPS:
    errstr = "NFS4ERR_TOO_MANY_OPS";
    break;
  case (int)NFS4ERR_TOOSMALL:
    errstr = "NFS4ERR_TOOSMALL";
    break;
  case (int)NFS4ERR_SYMLINK:
    errstr = "NFS4ERR_SYMLINK";
    break;
  case (int)NFS4ERR_STALE_STATEID:
    errstr = "NFS4ERR_STALE_STATEID";
    break;
  case (int)NFS4ERR_STALE_CLIENTID:
    errstr = "NFS4ERR_STALE_CLIENTID";
    break;
  case (int)NFS4ERR_STALE:
    errstr = "NFS4ERR_STALE";
    break;
  case (int)NFS4ERR_SHARE_DENIED:
    errstr = "NFS4ERR_SHARE_DENIED";
    break;
  case (int)NFS4ERR_SERVERFAULT:
    errstr = "NFS4ERR_SERVERFAULT";
    break;
  case (int)NFS4ERR_SEQ_MISORDERED:
    errstr = "NFS4ERR_SEQ_MISORDERED";
    break;
  case (int)NFS4ERR_SEQ_FALSE_RETRY:
    errstr = "NFS4ERR_SEQ_FALSE_RETRY";
    break;
  case (int)NFS4ERR_SEQUENCE_POS:
    errstr = "NFS4ERR_SEQUENCE_POS";
    break;
  case (int)NFS4ERR_SAME:
    errstr = "NFS4ERR_SAME";
    break;
  case (int)NFS4ERR_ROFS:
    errstr = "NFS4ERR_ROFS";
    break;
  case (int)NFS4ERR_RETURNCONFLICT:
    errstr = "NFS4ERR_RETURNCONFLICT";
    break;
  case (int)NFS4ERR_RETRY_UNCACHED_REP:
    errstr = "NFS4ERR_RETRY_UNCACHED_REP";
    break;
  case (int)NFS4ERR_RESTOREFH:
    errstr = "NFS4ERR_RESTOREFH";
    break;
  case (int)NFS4ERR_RESOURCE:
    errstr = "NFS4ERR_RESOURCE";
    break;
  case (int)NFS4ERR_REQ_TOO_BIG:
    errstr = "NFS4ERR_REQ_TOO_BIG";
    break;
  case (int)NFS4ERR_REP_TOO_BIG_TO_CACHE:
    errstr = "NFS4ERR_REP_TOO_BIG_TO_CACHE";
    break;
  case (int)NFS4ERR_REP_TOO_BIG:
    errstr = "NFS4ERR_REP_TOO_BIG";
    break;
  case (int)NFS4ERR_REJECT_DELEG:
    errstr = "NFS4ERR_REJECT_DELEG";
    break;
  case (int)NFS4ERR_RECLAIM_CONFLICT:
    errstr = "NFS4ERR_RECLAIM_CONFLICT";
    break;
  case (int)NFS4ERR_RECLAIM_BAD:
    errstr = "NFS4ERR_RECLAIM