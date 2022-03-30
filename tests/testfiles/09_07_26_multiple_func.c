int main(){
    int a = 2;
    return toto(a) + toto2(a);
}

int toto(int a){
    a = a + 1;
    return a+3;
}

int toto2(int a){
    a = a * 2;
    return a+5;
}