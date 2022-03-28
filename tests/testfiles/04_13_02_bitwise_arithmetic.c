int main() {
    int a = 3;
    int b = 5;
    int d = 7;
    int e = 10;
    int f = 2;
    int g = 8;
    int c = (a ^ b) | f*(d & e) + g;
    return c;
}