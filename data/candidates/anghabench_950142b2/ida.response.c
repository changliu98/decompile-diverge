const char *__cdecl nfs_error_string(int status)
{
  const char *v2; // [rsp+10h] [rbp-8h]

  switch ( status )
  {
    case 128:
      v2 = "NFS4_OK";
      break;
    case 129:
      v2 = "NFS4ERR_XDEV";
      break;
    case 130:
      v2 = "NFS4ERR_WRONG_TYPE";
      break;
    case 131:
      v2 = "NFS4ERR_WRONG_CRED";
      break;
    case 132:
      v2 = "NFS4ERR_WRONGSEC";
      break;
    case 133:
      v2 = "NFS4ERR_UNSAFE_COMPOUND";
      break;
    case 134:
      v2 = "NFS4ERR_UNKNOWN_LAYOUTTYPE";
      break;
    case 135:
      v2 = "NFS4ERR_TOO_MANY_OPS";
      break;
    case 136:
      v2 = "NFS4ERR_TOOSMALL";
      break;
    case 137:
      v2 = "NFS4ERR_SYMLINK";
      break;
    case 138:
      v2 = "NFS4ERR_STALE_STATEID";
      break;
    case 139:
      v2 = "NFS4ERR_STALE_CLIENTID";
      break;
    case 140:
      v2 = "NFS4ERR_STALE";
      break;
    case 141:
      v2 = "NFS4ERR_SHARE_DENIED";
      break;
    case 142:
      v2 = "NFS4ERR_SERVERFAULT";
      break;
    case 143:
      v2 = "NFS4ERR_SEQ_MISORDERED";
      break;
    case 144:
      v2 = "NFS4ERR_SEQ_FALSE_RETRY";
      break;
    case 145:
      v2 = "NFS4ERR_SEQUENCE_POS";
      break;
    case 146:
      v2 = "NFS4ERR_SAME";
      break;
    case 147:
      v2 = "NFS4ERR_ROFS";
      break;
    case 148:
      v2 = "NFS4ERR_RETURNCONFLICT";
      break;
    case 149:
      v2 = "NFS4ERR_RETRY_UNCACHED_REP";
      break;
    case 150:
      v2 = "NFS4ERR_RESTOREFH";
      break;
    case 151:
      v2 = "NFS4ERR_RESOURCE";
      break;
    case 152:
      v2 = "NFS4ERR_REQ_TOO_BIG";
      break;
    case 153:
      v2 = "NFS4ERR_REP_TOO_BIG_TO_CACHE";
      break;
    case 154:
      v2 = "NFS4ERR_REP_TOO_BIG";
      break;
    case 155:
      v2 = "NFS4ERR_REJECT_DELEG";
      break;
    case 156:
      v2 = "NFS4ERR_RECLAIM_CONFLICT";
      break;
    case 157:
      v2 = "NFS4ERR_RECLAIM_BAD";
      break;
    case 158:
      v2 = "NFS4ERR_RECALLCONFLICT";
      break;
    case 159:
      v2 = "NFS4ERR_PNFS_NO_LAYOUT";
      break;
    case 160:
      v2 = "NFS4ERR_PNFS_IO_HOLE";
      break;
    case 161:
      v2 = "NFS4ERR_PERM";
      break;
    case 162:
      v2 = "NFS4ERR_OP_NOT_IN_SESSION";
      break;
    case 163:
      v2 = "NFS4ERR_OP_ILLEGAL";
      break;
    case 164:
      v2 = "NFS4ERR_OPENMODE";
      break;
    case 165:
      v2 = "NFS4ERR_OLD_STATEID";
      break;
    case 166:
      v2 = "NFS4ERR_NXIO";
      break;
    case 167:
      v2 = "NFS4ERR_NO_GRACE";
      break;
    case 168:
      v2 = "NFS4ERR_NOT_SAME";
      break;
    case 169:
      v2 = "NFS4ERR_NOT_ONLY_OP";
      break;
    case 170:
      v2 = "NFS4ERR_NOTSUPP";
      break;
    case 171:
      v2 = "NFS4ERR_NOTEMPTY";
      break;
    case 172:
      v2 = "NFS4ERR_NOTDIR";
      break;
    case 173:
      v2 = "NFS4ERR_NOSPC";
      break;
    case 174:
      v2 = "NFS4ERR_NOMATCHING_LAYOUT";
      break;
    case 175:
      v2 = "NFS4ERR_NOFILEHANDLE";
      break;
    case 176:
      v2 = "NFS4ERR_NOENT";
      break;
    case 177:
      v2 = "NFS4ERR_NAMETOOLONG";
      break;
    case 178:
      v2 = "NFS4ERR_MOVED";
      break;
    case 179:
      v2 = "NFS4ERR_MLINK";
      break;
    case 180:
      v2 = "NFS4ERR_MINOR_VERS_MISMATCH";
      break;
    case 181:
      v2 = "NFS4ERR_LOCK_RANGE";
      break;
    case 182:
      v2 = "NFS4ERR_LOCK_NOTSUPP";
      break;
    case 183:
      v2 = "NFS4ERR_LOCKS_HELD";
      break;
    case 184:
      v2 = "NFS4ERR_LOCKED";
      break;
    case 185:
      v2 = "NFS4ERR_LEASE_MOVED";
      break;
    case 186:
      v2 = "NFS4ERR_LAYOUTUNAVAILABLE";
      break;
    case 187:
      v2 = "NFS4ERR_LAYOUTTRYLATER";
      break;
    case 188:
      v2 = "NFS4ERR_ISDIR";
      break;
    case 189:
      v2 = "NFS4ERR_IO";
      break;
    case 190:
      v2 = "NFS4ERR_INVAL";
      break;
    case 191:
      v2 = "NFS4ERR_HASH_ALG_UNSUPP";
      break;
    case 192:
      v2 = "NFS4ERR_GRACE";
      break;
    case 193:
      v2 = "NFS4ERR_FILE_OPEN";
      break;
    case 194:
      v2 = "NFS4ERR_FHEXPIRED";
      break;
    case 195:
      v2 = "NFS4ERR_FBIG";
      break;
    case 196:
      v2 = "NFS4ERR_EXPIRED";
      break;
    case 197:
      v2 = "NFS4ERR_EXIST";
      break;
    case 198:
      v2 = "NFS4ERR_ENCR_ALG_UNSUPP";
      break;
    case 199:
      v2 = "NFS4ERR_DQUOT";
      break;
    case 200:
      v2 = "NFS4ERR_DIRDELEG_UNAVAIL";
      break;
    case 201:
      v2 = "NFS4ERR_DENIED";
      break;
    case 202:
      v2 = "NFS4ERR_DELEG_REVOKED";
      break;
    case 203:
      v2 = "NFS4ERR_DELEG_ALREADY_WANTED";
      break;
    case 204:
      v2 = "NFS4ERR_DELAY";
      break;
    case 205:
      v2 = "NFS4ERR_DEADSESSION";
      break;
    case 206:
      v2 = "NFS4ERR_DEADLOCK";
      break;
    case 207:
      v2 = "NFS4ERR_CONN_NOT_BOUND_TO_SESSION";
      break;
    case 208:
      v2 = "NFS4ERR_COMPLETE_ALREADY";
      break;
    case 209:
      v2 = "NFS4ERR_CLIENTID_BUSY";
      break;
    case 210:
      v2 = "NFS4ERR_CLID_INUSE";
      break;
    case 211:
      v2 = "NFS4ERR_CB_PATH_DOWN";
      break;
    case 212:
      v2 = "NFS4ERR_BAD_STATEID";
      break;
    case 213:
      v2 = "NFS4ERR_BAD_SESSION_DIGEST";
      break;
    case 214:
      v2 = "NFS4ERR_BAD_SEQID";
      break;
    case 215:
      v2 = "NFS4ERR_BAD_RANGE";
      break;
    case 216:
      v2 = "NFS4ERR_BAD_HIGH_SLOT";
      break;
    case 217:
      v2 = "NFS4ERR_BAD_COOKIE";
      break;
    case 218:
      v2 = "NFS4ERR_BADXDR";
      break;
    case 219:
      v2 = "NFS4ERR_BADTYPE";
      break;
    case 220:
      v2 = "NFS4ERR_BADSLOT";
      break;
    case 221:
      v2 = "NFS4ERR_BADSESSION";
      break;
    case 222:
      v2 = "NFS4ERR_BADOWNER";
      break;
    case 223:
      v2 = "NFS4ERR_BADNAME";
      break;
    case 224:
      v2 = "NFS4ERR_BADLAYOUT";
      break;
    case 225:
      v2 = "NFS4ERR_BADIOMODE";
      break;
    case 226:
      v2 = "NFS4ERR_BADHANDLE";
      break;
    case 227:
      v2 = "NFS4ERR_BADCHAR";
      break;
    case 228:
      v2 = "NFS4ERR_BACK_CHAN_BUSY";
      break;
    case 229:
      v2 = "NFS4ERR_ATTRNOTSUPP";
      break;
    case 230:
      v2 = "NFS4ERR_ADMIN_REVOKED";
      break;
    case 231:
      v2 = "NFS4ERR_ACCESS";
      break;
    default:
      v2 = "invalid nfs error code";
      break;
  }
  return v2;
}