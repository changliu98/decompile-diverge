int roundUp(int numToRound, int multiple) {
  int numRoundedUp;
  int numRoundedDown = (numToRound / multiple) * multiple;
  int numRoundedUpValue = (numToRound / multiple + 1) * multiple;

  if (numToRound - numRoundedDown > numRoundedUpValue - numToRound) {
    numRoundedUp = numRoundedUpValue;
  } else {
    numRoundedUp = numRoundedDown;
  }

  return numRoundedUp;
}