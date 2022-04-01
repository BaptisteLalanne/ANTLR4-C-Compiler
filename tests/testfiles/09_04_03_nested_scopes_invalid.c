int toto(int a, int b, int c) {
    int result = a+b+c;
    return result;
}

int main() {
    int a = 1;
    int res = 0;
    {
       int b = 0;
       int c = a+b;
       res = toto(c, c, c);
    }
    return c;
}