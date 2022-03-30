int titi(int a) {
    return a;
}

int tata(int p) {
    return titi(p+3);
}

int toto(int a, int b, int c) {
    int result = a+b+c;
    return tata(result);
}

int main() {
    int c = 1;
    int a = toto(1, 1+1, c*3) + 1;
    return a;
}