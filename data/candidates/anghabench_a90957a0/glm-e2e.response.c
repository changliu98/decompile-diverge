const char *mptcp_event_to_str(int event) {
    const char *str = "Unknown event";
    
    switch (event) {
        case 0x80:
            str = "MPTCP_EVENT_CREATED";
            break;
        case 0x81:
            str = "MPTCP_EVENT_ESTABLISHED";
            break;
        case 0x82:
            str = "MPTCP_EVENT_CLOSED";
            break;
        default:
            break;
    }
    
    return str;
}