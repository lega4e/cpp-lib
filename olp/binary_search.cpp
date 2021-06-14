/*
 * autor:   nvx
 * created: Nov  3 14:11:21 2019
 */





// function
int *binary_search(int *b, int *e, int val)
{
	--b;
	int *m;
	while(e-b > 1)
	{
		m = (b + e) / 2;
		/*
		 * for lower bound: <=
		 * for upper bound: <
		 */
		if(val < *m)
			e = m;
		else
			b = m;
	}
	return e;
}





// end
