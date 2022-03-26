int toto(int a, int b, int c) {
    int result = a+b+c;
    return result;
}

int main() {
    int c = 1;
    int a = toto(1, 1+1, c*3) + 1;
    return a;
}