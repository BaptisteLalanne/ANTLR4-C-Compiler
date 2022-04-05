int toto() {
    int a = 5;
    while (a > 0) {
        a = a-1;
    }
    return a + 10;
}

int tata() {
    return toto() + 5;
}

int main() {
    int a = 0;
    int b = 1;
    int c = toto();
    int d = tata();
    int res = (c*1) + (c-0) + (c+a) * (d/b);
    return res;
}