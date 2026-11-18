VL53L0X_Error VL53L0X_PerformSingleHistogramMeasurement(VL53L0X_DEV Dev,
        VL53L0X_HistogramMeasurementData_t *pHistogramMeasurementData) {
    VL53L0X_Error Status = ((VL53L0X_Error) 0);
    (void)0;

    (Dev->Data.PalState)=(((VL53L0X_State)(Dev->Data.PalState))+1);


    if (Status == ((VL53L0X_Error) 0))
        Status |= VL53L0X_perform_single_histogram_measurement(Dev,
            pHistogramMeasurementData);

    (void)0;
    return Status;
}