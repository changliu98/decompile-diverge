double func0(int quantity)
{
  double base_price;
  int tax_fee;

  // If units are less than 50 (0x32)
  if (quantity < 0x32) {
    // Calculate base amount for the first tier
    base_price = (double)quantity * tier1_rate;
    // Set surcharge for the first tier
    tax_fee = 0x19;
  }
  // If units are between 50 (0x32) and 101 (0x65)
  else if (quantity < 0x65) {
    // Calculate base amount for the second tier, adjusting for the first tier's capacity
    base_price = (double)(quantity - 0x32) * tier2_rate + tier2_base;
    // Set surcharge for the second tier
    tax_fee = 0x23;
  }
  // If units are between 101 (0x65) and 201 (0xc9)
  else if (quantity < 0xc9) {
    // Calculate base amount for the third tier, adjusting for the first two tiers' capacity
    base_price = (double)(quantity - 100) * tier3_rate + tier3_base;
    // Set surcharge for the third tier
    tax_fee = 0x2d;
  }
  // If units are 201 (0xc9) or more
  else {
    // Calculate base amount for the fourth tier, adjusting for the first three tiers' capacity
    base_price = (double)(quantity - 200) * tier4_rate + tier4_base;
    // Set surcharge for the fourth tier
    tax_fee = 0x4b;
  }
  // Return the total amount including the surcharge
  return base_price + (double)tax_fee;
}