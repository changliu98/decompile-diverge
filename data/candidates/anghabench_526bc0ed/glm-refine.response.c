define ROCCAT_FEATURE_REPORT_BASE 0x300

uint16_t __cdecl roccat_common2_feature_report(uint8_t report_id)
{
    return ROCCAT_FEATURE_REPORT_BASE | report_id;
}