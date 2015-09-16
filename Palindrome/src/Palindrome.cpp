#include <iostream>
 
bool isPalindrome(int x) {
    if (x < 0) {
        return false;
    }
 
    int curr = x;
    int rev = 0;
 
    while (curr) {
        int z = curr % 10;
        curr /= 10;
        rev = (rev * 10) + z;
    }
 
    return x == rev;
}
 
void checkPalindrome(int x) {
	std::cout << x << ": " << isPalindrome(x) << std::endl;
}
 
int main(int argc, char* argv[]) {
	checkPalindrome(-1);
	checkPalindrome(0);
	checkPalindrome(1);
	checkPalindrome(11);
	checkPalindrome(1234);
	checkPalindrome(123321);
	checkPalindrome(1234321);
	checkPalindrome(9887889);

	return 0;
}