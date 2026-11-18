unsigned int uniphier_gpio_bank_to_reg(unsigned int bank) {
    unsigned int reg = (bank + 1) << 3;
    
    if (reg >= UNIPHIER_GPIO_IRQ_EN) {
        reg += 0x10;
    }
    
    return reg;
}