int toto(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
    return a+b+c+d+e+f+g+h+i;
}

int main() {
    int a = 0;
    int c = 0;
    while (c < 5) {
        c = c+1;
    }
    return toto(0, 1, 5, 1, 12, c, 5, 79, a);
}