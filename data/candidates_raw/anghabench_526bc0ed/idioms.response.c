static unsigned short hci_get_data_size(unsigned char report_id)
{
  return (report_id | (sizeof(struct hci_data_header) - sizeof(struct hci_header)));
}