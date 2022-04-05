int toto3(){
    return 2;
}

int toto3(){
    return toto4();
}

int main(){
    return toto();
}

int toto(){
    return toto2();
}

int toto2(){
    return toto3();
}

int toto5(){
    return toto6();
}

int toto6(){
    return toto7();
}

int toto7(){
    return 7;
}