int
zero()
{
	return 0;
}

int
one()
{
	return 1;
}

int
main()
{
	int x;
	int y;
	
	x = zero();
	x+=1;
	y = x;
	if (x != 1)
		return 1;
	if (y != 1)
		return 1;
	
	x = one();	
	x-=1;
	y = x;

	if (x != 0)
		return 1;
	if (y != 0)
		return 1;
	
	x = zero();
	y = x;
	x+=1;
	if (x != 1)
		return 1;
	if (y != 0)
		return 1;
	
	x = one();
	y = x;
	x-=1;
	if (x != 0)
		return 1;
	if (y != 1)
		return 1;
	
	return 0;
}
