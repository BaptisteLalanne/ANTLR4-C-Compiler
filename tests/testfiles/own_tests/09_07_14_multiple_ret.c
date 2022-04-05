int main() {
    int a = 5;
    a = toto(a);
    return a;
}

int toto(int a){
    if(a < 10){
       a = a + 3;
    }else{
       return toto(a);
    }
    return a + 10;
}