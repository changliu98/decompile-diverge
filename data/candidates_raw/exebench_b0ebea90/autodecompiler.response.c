int SendCW(int ModemFD, char *CWBuffer)
{
 int nReturnVal;





 if ((long) send(ModemFD, CWBuffer, 18, 0) == -1) {
   syslog(3, "ca.so: Send cw failed %d", (*___errno_location ()));
   nReturnVal = 0;
 }
 else {
   nReturnVal = 1;
 }

 return nReturnVal;
}