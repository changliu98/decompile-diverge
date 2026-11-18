char *get_mpce_event_name(int event)
{
 char *name = "UNDEFINED";

 switch(event) {
 case MPCE_CLOSE:
  name = "MPCE_CLOSE";
  break;
 case MPCE_RECV_DATA_ACK:
  name = "MPCE_RECV_DATA_ACK";
  break;
 case MPCE_RECV_DATA_FIN:
  name = "MPCE_RECV_DATA_FIN";
 }

 return name;
}