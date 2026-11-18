char * mptcp_event_to_str(uint32_t event)

{
  char *c;
  uint32_t event_local;
  
  c = "UNDEFINED";
  if (event == 0x80) {
    c = "MPCE_RECV_DATA_FIN";
  }
  else if (event == 0x81) {
    c = "MPCE_RECV_DATA_ACK";
  }
  else if (event == 0x82) {
    c = "MPCE_CLOSE";
  }
  return c;
}