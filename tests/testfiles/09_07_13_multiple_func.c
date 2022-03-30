int toto3 (int a){
	return a + 1;
}

int toto(int a) {
	return a + 1;
}

int toto2(int a){
	return a + 1;
}

int main() {
    int a = 5;
    a = toto(toto2(toto3(toto4(a))));
    return a;
}

int toto4(int a){
	return a + 1;
}