int write_sock(int sock,char *msg,int p_numofBytes)
{
 int nSend = -1;

 nSend = write(sock,msg,p_numofBytes,0);

 return p_numofBytes-nSend;
}