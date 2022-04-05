int main() {
    int a=0;
    int b=0;
    while(b<5){
        while(a<5){
            if (a%2) {
                a = 4*a;
            } else {
                b = a & 5;
            }
            a=a+1;
        }
        b = b+1;
    }
    return a+b;
}