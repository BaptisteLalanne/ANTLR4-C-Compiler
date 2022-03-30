int toto(int a) {
	int a = a + 1;
	return a;
}

int main() {
    int a = 5;
    a = toto(a);
    return a;
}