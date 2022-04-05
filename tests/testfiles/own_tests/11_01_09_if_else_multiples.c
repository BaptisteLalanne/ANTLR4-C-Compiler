int main() {
    int a=5;
    int b=1;
    if (a==5) {
        b=2;
        if (a==5) {
            b=3;
            if (a!=5) {
                b=4;
                if (a==5) {
                    b=5;
                    if (a==5) {
                        b=6;
                    } else {
                        b=7;
                    }
                }
            } else {
                b=11;
            }
        }
    } else {
        b = 8;
        if(a==5){
            b=9;
        } else {
            b=10;
        }
    }

    return b;
}