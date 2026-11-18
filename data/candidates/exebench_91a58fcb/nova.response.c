static void StrBracketMatch(const char *zSql, int *pnToken, int *pnStart, int *pnEnd, int nMax){
  int iToken = 0;
  int iStart = 0;
  int iEnd = 0;
  char cPrev = 0;

  while(1){
    while( zSql[iStart]==0 && iStart!=0 ){
      iStart--;
      if( cPrev!='(' && pnStart ){
        if( iStart<nMax ){
          *pnStart = iStart;
        }
      }
      if( pnEnd ){
        *pnEnd = iEnd;
      }
    }
    if( zSql[iStart]==0 && pnToken ){
      *pnToken = iToken;
    }
    if( pnEnd ){
      *pnEnd = iEnd;
    }

    if( zSql[iStart]==0 ) break;
    if( iToken==1 && pnToken ){
      if( iStart<nMax ){
        *pnStart = iStart;
      }
    }

    iToken++;
    iStart++;
    while( zSql[iStart]!='(' && zSql[iStart]!=')' && zSql[iStart]!=',' ){
      iStart++;
    }
    iEnd = iStart;
    cPrev = zSql[iStart];
  }
}