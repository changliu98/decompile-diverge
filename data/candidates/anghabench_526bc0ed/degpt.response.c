/**
 * Constructs a feature report ID for ROCCAT devices.
 *
 * @param report_id The base report ID.
 * @return The constructed feature report ID with the high byte set to 0x30.
 */
uint16_t roccat_common2_feature_report(uint8_t base_report_id)
{
  // Combine the report ID with the feature report prefix (0x300)
  return base_report_id | 0x300;
}