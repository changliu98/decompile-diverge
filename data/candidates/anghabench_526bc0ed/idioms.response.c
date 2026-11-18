static unsigned short roccat_common2_feature_report(unsigned char report_id)
{
  return (report_id | (sizeof(struct hci_data_header) - sizeof(struct hci_header)));
}