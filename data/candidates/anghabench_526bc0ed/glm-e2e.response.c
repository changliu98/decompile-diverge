uint16_t roccat_common2_feature_report(uint8_t report_id) {
    return (uint16_t)(report_id | 0x300);
}