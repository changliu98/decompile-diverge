const char *mptcp_event_to_str(uint32_t event)
{
  switch (event)
  {
    case 0x80:
      return "MPCE_RECV_DATA_FIN";
    case 0x81:
      return "MPCE_RECV_DATA_ACK";
    case 0x82:
      return "MPCE_CLOSE";
    default:
      return "UNDEFINED";
  }
}