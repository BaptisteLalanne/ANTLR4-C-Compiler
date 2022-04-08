char generate(char p1, char _c_12, char bit, int n) {
	char n2 = bit/n;
	return p1 + _c_12 + n2;
}

int
main(void) 
{
	int n, t;
	int c = fact(fact(2)) + fact(5);
	int p;
	char a = generate('a', 'c', '0', 2);

	n = 2 + a;
	while (n < 5000) {
		t = 2;
		p = 1;
		while (t*t <= n) {
			if (n % t == 0)
				p = 0;
			t+=1;
		}
		n += 1;
		if (p) {
			c += 1;
		}
		else {
			c -= 1;
		}
	}
	if (c != 669)
		return 1;
	return 0;
}

int fact(int n){
    if(n==0){
       return 1;
    }
    return n * fact(n-1);
}
