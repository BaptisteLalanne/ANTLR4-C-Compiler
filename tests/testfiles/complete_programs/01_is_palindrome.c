#include <stdio.h>

void printInt(int x){

    while(x>0){
        putchar(x%10 + '0');
        x = x/10;
    }

}

int isPalindrome(int x){
    putchar('i');
    putchar('s');
    putchar('P');
    putchar('P');
    putchar('a');
    putchar('l');
    putchar('i');
    putchar('n');
    putchar('d');
    putchar('r');
    putchar('o');
    putchar('m');
    putchar('e');
    putchar(' ');
    putchar('?');
    putchar(' ');
    printInt(x);
    putchar(' ');
    putchar(':');
    putchar(' ');

    if(x < 0){
        return -1;
    }
    int ori = x;
    int sum = 0;
    while(x > 0){
        sum = (sum * 10) + (x % 10);
        x = x / 10;
    }
    if(sum == ori){
        putchar('T');
        putchar('r');
        putchar('u');
        putchar('e');
        putchar(' ');
        putchar('!');
        putchar(10);
        return 1;
    } else {
        putchar('F');
        putchar('a');
        putchar('l');
        putchar('s');
        putchar('e');
        putchar(' ');
        putchar('!');
        putchar(10);
        return -1;
    }
}



int main() {
    int value = 0;
    value = value + isPalindrome(1);
    value = value + isPalindrome(983649);
    value = value + isPalindrome(736637);
    value = value + isPalindrome(3735);
    value = value + isPalindrome(1234567890);
    value = value + isPalindrome(1234567890987654321);
    value = value + isPalindrome(12345678900987654321);
    value = value + isPalindrome(3864893);
    value = value + isPalindrome(872942);
    value = value + isPalindrome(938735);
    value = value + isPalindrome(376539);
    value = value + isPalindrome(123456773654);
    value = value + isPalindrome(23455432);
    value = value + isPalindrome(98766789);
    value = value + isPalindrome(9387935);
    value = value + isPalindrome(45677654);
    value = value + isPalindrome(938839);
    value = value + isPalindrome(98389);
    value = value + isPalindrome(29867548737);
    return value;
}