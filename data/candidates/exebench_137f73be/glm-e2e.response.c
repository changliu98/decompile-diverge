int I2CSensor_Read(struct I2CSensorContext *ctx, unsigned char slave_addr, unsigned char reg_addr, char *buf, int len) {
    int ret = 3; // Default error code used in all failure paths

    // Step 1: Set the I2C slave address via ioctl
    // 0x0703 corresponds to the I2C_SLAVE constant in <linux/i2c-dev.h>
    if (ioctl(ctx->fd, 0x0703, slave_addr) >= 0) {
        
        // Step 2: Write the register address to the device
        if (write(ctx->fd, &reg_addr, 1) == 1) {
            
            // Step 3: Read 'len' bytes from the device into the buffer
            if (read(ctx->fd, buf, len) == len) {
                ret = 0; // Success
            }
        }
    }
    
    return ret;
}