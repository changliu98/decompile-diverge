/**
 * qcom_nandc_calc_ecc_bytes - Calculate ECC bytes based on strength
 * @step_size: NAND step size (unused in current implementation)
 * @strength: ECC correction strength
 *
 * Returns the number of ECC bytes required:
 * - 0xc (12) bytes for strength 4
 * - 0x10 (16) bytes for other strengths
 */
int qcom_nandc_calc_ecc_bytes(int unused_param, int ecc_strength)
{
    return ecc_strength == 4 ? 0xc : 0x10;
}