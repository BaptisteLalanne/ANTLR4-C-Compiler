int main() {
    int a=1;
    int b=2;
    while(b<3){
        b = 4;
        while(a<5){
            a = 6;
        }
        b = 7;
    }
    return a+b;
}