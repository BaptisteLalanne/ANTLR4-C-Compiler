int fact(int n){
    if(n==0){
       return 1;
    }
    return n * fact(n-1);
}

int main(){
    return fact(1) + fact(5) + fact(10) + fact (50);
}
