int toto(char a, int b, int c, int d, int e, int f, int g, int h, char i) {
    return a+b+c+d+e+f+g+h+i;
}

char nonConstChar() {
    return 'p';
}

int main() {
    char a = nonConstChar();
    int c = 1;
    return toto('a', 0, 0, 0, 0, c, 0, 1, a);
}