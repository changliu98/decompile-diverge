int qcom_nandc_calc_ecc_bytes(int step_size, int data) {
    int ecc_bytes = 16;
    
    if (data == 4) {
        ecc_bytes = 12;
    }
    
    return ecc_bytes;
}