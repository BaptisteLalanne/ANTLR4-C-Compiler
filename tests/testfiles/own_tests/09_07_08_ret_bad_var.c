int toto() {
	int a = 1+1;
	return toto2();
}

int toto2(){
	return a;
}

int main() {
    int a = toto();
    return a;
}