int toto(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
    return a+b+c+d+e+f+g+h+i;
}

int main() {
    int p = 0;
    while (p < 10) {
        p = p+1;
    }
    int a = toto(5, 1, 1, 1, 1, 1, p, 20, 50);
    int b = a*2;
    return b-5;
}