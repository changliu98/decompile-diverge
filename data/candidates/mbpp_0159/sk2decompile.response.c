char *func0(char *month, int day) {
  char *season;
  if (!strcmp(month, "January") || !strcmp(month, "February") ||
      !strcmp(month, "March")) {
    season = "winter";
  } else if (!strcmp(month, "April") || !strcmp(month, "May") ||
             !strcmp(month, "June")) {
    season = "spring";
  } else if (!strcmp(month, "July") || !strcmp(month, "August") ||
             !strcmp(month, "September")) {
    season = "summer";
  } else {
    season = "autumn";
  }
  if ((!strcmp(month, "March") && day > 19) ||
      (!strcmp(month, "June") && day > 20) ||
      (!strcmp(month, "September") && day > 21)) {
    if (!strcmp(month, "March")) season = "spring";
    if (!strcmp(month, "June")) season = "summer";
    if (!strcmp(month, "September")) season = "autumn";
  } else if (!strcmp(month, "December") && day > 20) {
    season = "winter";
  }
  return season;
}