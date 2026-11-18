define I2C_READ_FAILURE 3

int I2CSensor_Read(int *bus, unsigned char I2CAddress, unsigned char registry, unsigned char *buffer, int size)
{
    // Set the I2C slave address via ioctl
    if (ioctl(*bus, I2C_SLAVE, I2CAddress) < 0)
        return I2C_READ_FAILURE;

    // Write the registry address to the bus to tell the sensor what we want to read
    if (write(*bus, &registry, 1) != 1)
        return I2C_READ_FAILURE;

    // Read the requested number of bytes from the bus into the buffer
    if (read(*bus, buffer, size) == size)
        return I2C_READ_SUCCESS;

    return I2C_READ_FAILURE;
}