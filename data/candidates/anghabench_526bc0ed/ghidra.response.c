uint16_t roccat_common2_feature_report(uint8_t report_id)

{
  uint8_t report_id_local;
  
  return report_id | 0x300;
}