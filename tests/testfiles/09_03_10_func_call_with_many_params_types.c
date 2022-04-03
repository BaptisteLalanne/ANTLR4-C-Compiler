int toto(char a, int b, int c, char d, int e, int f, int g, int h, char i) {
    return a+b+c+d+e+f+g+h+i;
}

int main() {
    char a = 'P';
    int c = 0;
    while (c < 5) {
        c = c+1;
    }
    return toto('a', 1, 5, 't', 12, c, 5, 79, a);
}