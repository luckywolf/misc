/*
A palindromic number reads the same both ways. 
The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 x 99. 
Find the largest palindrome made from the product of two 3-digit numbers.
*/
/* c++ version */
#include <iostream>
using namespace std;

bool isPalindrome(int x) {
    int div = 100000;
    if (x < 100000) {
        div = 10000;
    }
    while (x >= 10) {
        if (x / div != x % 10) {
            return false;
        }
        x %= div;
        x /= 10;
        div /= 100;
    }
    return true;
}

int largestPalindrome() {
    int max = 0;
    for (int i = 999; i > 0; --i) {
        if (i * 999 < max) {
            break;
        }
        for (int j = 999; j > 0; --j) {
            int temp = i * j;
            if (isPalindrome(temp)) {
                if (temp > max) {
                     max = temp;
                }
                break;
            }
        }
    }
    return max;
}

int main() {  
  cout <<  largestPalindrome() << endl;  
}

/* python version */
#!/usr/local/bin/python2.7

def largestPalindrome():
    max = 0
    for x in xrange(999, 99, -1):
        if x * 999 < max:
            break;
        for y in xrange(999, 99, -1):
            temp = x * y;
            if str(temp) == str(temp)[::-1]:
                if temp > max:
                    max = temp;
                break;
    return max;

print "result is " , largestPalindrome()

