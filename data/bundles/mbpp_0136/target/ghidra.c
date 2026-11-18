double func0(int units)

{
  double total;
  int surcharge;
  double amount;
  int units_local;
  
  if (units < 0x32) {
    amount = (double)units * DAT_00102038;
    surcharge = 0x19;
  }
  else if (units < 0x65) {
    amount = (double)(units + -0x32) * DAT_00102028 + DAT_00102030;
    surcharge = 0x23;
  }
  else if (units < 0xc9) {
    amount = (double)(units + -100) * DAT_00102018 + DAT_00102020;
    surcharge = 0x2d;
  }
  else {
    amount = (double)(units + -200) * DAT_00102008 + DAT_00102010;
    surcharge = 0x4b;
  }
  return amount + (double)surcharge;
}