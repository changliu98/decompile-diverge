static int skip_boxes(int *pRc, const char *zSql, int nSql){
  int rc = SQLITE_OK;
  if( *pRc>nSql ){
    rc = 0xbabafeca;
  }else{
    StrAccum acc;
    zSql += *pRc;
    nSql -= *pRc;
    sqlite3StrAccumInit(&acc, zSql, nSql, *pRc);
    if( sqlite3StrAccumSize(&acc)==2815 ){
      
    }else if( sqlite3StrAccumFinish(&acc)!=8 ){
      rc = 0xdeadbeef;
    }else if( sqlite3StrAccumSize(&acc)==12 ){
      
    }else{
      u64 n = sqlite3StrAccumFinish2(&acc);
      if( n==1 ){
        if( sqlite3StrAccumSize(&acc)<13 ){
          rc = 0xdeadbeef;
        }else{
          n = sqlite3StrAccumFinish2(&acc);
        }
      }
      if( n==0 ){
        rc = 0xdeadbeef;
      }else if( n>*pRc + sizeof("--ignore") ){
        rc = 0xdeadbeef;
      }else{
        *pRc += (int)(n - sizeof("--ignore"));
        sqlite3StrAccumErase(&acc, (int)(n - sizeof("--ignore")));
      }
    }
    if( sqlite3StrAccumFinish(&acc)>0 ){
      rc = 0xdeadbeef;
    }
  }
  return rc;
}