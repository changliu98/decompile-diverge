int convertToBills(int amount, int *hundreds, int *fifties, int *twenties, int *tens) {
    *hundreds = amount / 100;
    *fifties = (amount % 100) / 50;
    *twenties = ((amount % 100) % 50) / 20;
    *tens = (((amount % 100) % 50) % 20) / 10;
    
    return amount % 10;
}