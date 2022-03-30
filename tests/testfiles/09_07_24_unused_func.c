int toto4(){
    return 2;
}

int toto3(){
    return toto4();
}

int main(){
    return 0;
}

int toto(){
    return toto2();
}

int toto2(){
    return toto3();
}