int SeekPoint( unsigned char *toc, int file_bytes, float percent )
{

 int seekpoint;
 int ipercent;
 float fpercent;
 float fseekpoint;


 if( percent < 0.0 )
  percent = 0.0;

 if( percent > 100.0 )
  percent = 100.0;


 ipercent = (int)percent;


 if( ipercent >= 100 )
  ipercent = 99;


 fpercent = percent - (float)ipercent;


 if( ipercent >= 99 )
  fseekpoint = (float)toc[ipercent];
 else
  fseekpoint = ((float)toc[ipercent] + (float)(toc[ipercent+1] - toc[ipercent]) * fpercent);


 fseekpoint *= 256.0;


 seekpoint = (int)( fseekpoint * (float)file_bytes );

 return( seekpoint );
}