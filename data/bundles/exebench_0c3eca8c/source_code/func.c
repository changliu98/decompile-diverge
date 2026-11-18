#include <stdio.h>

void expand( char compacted[], char expanded[] )
{
 int e, ee;


 if( ( compacted[ 0 ] >= '0' && compacted[ 0 ] <= '9' ) &&
  ( compacted[ 2 ] >= '0' && compacted[ 2 ] <= '9' ) &&
  ( compacted[ 0 ] <= compacted[ 2 ] ) )
 {
  for( e = compacted[ 0 ], ee = 0; e <= compacted[ 2 ]; ++e, ++ee )
  {
   expanded[ ee ] = e;
  }
  expanded[ ee ] = '\0';
 }

 else if( ( compacted[ 0 ] >= 'A' && compacted[ 0 ] <= 'Z' ) &&
    ( compacted[ 2 ] >= 'A' && compacted[ 2 ] <= 'Z' ) &&
    ( compacted[ 0 ] <= compacted[ 2 ] ) )
 {
  for( e = compacted[ 0 ], ee = 0; e <= compacted[ 2 ]; ++e, ++ee )
  {
   expanded[ ee ] = e;
  }
  expanded[ ee ] = '\0';
 }

 else if( ( compacted[ 0 ] >= 'a' && compacted[ 0 ] <= 'z' ) &&
    ( compacted[ 2 ] >= 'a' && compacted[ 2 ] <= 'z' ) &&
    ( compacted[ 0 ] <= compacted[ 2 ] ) )
 {
  for( e = compacted[ 0 ], ee = 0; e <= compacted[ 2 ]; ++e, ++ee )
  {
   expanded[ ee ] = e;
  }
  expanded[ ee ] = '\0';
 }
}
