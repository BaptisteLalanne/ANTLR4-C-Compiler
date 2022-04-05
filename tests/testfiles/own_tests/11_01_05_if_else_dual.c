int main() {
    int a=42;
    if (a==5) {
        a = 2;
    } else {
        a = 3;
        if (a == 4) {
            a = 4;
        } else {
            a = 5;
        }
    }

    int c = a * 10;

    return c;
}