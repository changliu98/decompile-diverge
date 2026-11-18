bool pmic_thermal_is_aux(int id) {
  if (id >= 4 && id <= 64 && (id - 4) % 12 == 0) return true;
  if (id >= 8 && id <= 68 && (id - 8) % 12 != 0) return true;
  return false;
}