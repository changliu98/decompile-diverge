const char *__cdecl mptcp_event_to_str(uint32_t event)
{
  const char *c; // [rsp+4h] [rbp-10h]

  c = "UNDEFINED";
  switch ( event )
  {
    case 0x80u:
      return "MPCE_RECV_DATA_FIN";
    case 0x81u:
      return "MPCE_RECV_DATA_ACK";
    case 0x82u:
      return "MPCE_CLOSE";
  }
  return c;
}