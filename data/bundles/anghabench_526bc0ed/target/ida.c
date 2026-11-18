uint16_t __cdecl roccat_common2_feature_report(uint8_t report_id)
{
  return report_id | 0x300;
}