char *mpce_event2str(unsigned int event)
{
 char *str = "UNDEFINED";
 switch (event) {
  case 0x80:
   str = "MPCE_RECV_DATA_FIN";
   break;
  case 0x81:
   str = "MPCE_RECV_DATA_ACK";
   break;
  case 0x82:
   str = "MPCE_CLOSE";
   break;
 }
 return str;
}