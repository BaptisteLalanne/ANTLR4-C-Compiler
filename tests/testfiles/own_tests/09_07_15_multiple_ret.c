int main() {
    int a = 5;
    a = toto(a);
    return a;
}

int toto(int a){
    if(a < 10){
       a = a + 3;
       return a + 10;
    }else{
       return toto(a);
    }
}