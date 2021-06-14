/*
 * autor:   nvx
 * created: Jan 27 00:37:36 2021
 */





/*
 * Дерево отрезков, построенное с помощью
 * указателей
 */
struct Cut
{
	int val;
	int l, r, m;
	Cut *left, *right;


	void init(int const *s, int ll, int rr)
	{
		l = ll;
		r = rr;
		m = (l + r)/2;
		if(l == r)
		{
			left = nullptr;
			right = nullptr;
			val = s[l];
			return;
		}

		left = new Cut;
		left->init(s, l, m);
		right = new Cut;
		right->init(s, m+1, r);

		val = left->val + right->val;
		return;
	}

	void free()
	{
		if(left)
		{
			left->free();
			delete left;
		}

		if(right)
		{
			right->free();
			delete right;
		}

		return;
	}

	int get(int ll, int rr) const
	{
		if(ll == l and rr == r)
			return val;

		if(rr <= m)
			return left->get(ll, rr);

		if(ll >= m+1)
			return right->get(ll, rr);

		return
			left->get(ll, m) +
			right->get(m+1, rr);
	}
};





/*
 * Дерево отрезков, постренное с
 * помощью массива
 */
template<typename Cut>
struct Tree
{
	vector<Cut> cuts;

	void init(char const *s, int n)
	{
		cuts.resize( (int) pow( 2, ceil(log2(n)) + 1 ) - 1 );
		cuts[0].init(*this, s, 0, n-1);
		return;
	}

	auto operator()(int l, int r)
	{
		return cuts[0].get(*this, l, r);
	}

	Cut &operator()(Cut const *cut, int i)
	{
		return child(cut, i);
	}
};



struct Cut
{
	int val;
	int l, r;

	void init(Tree<Cut> &tree, int const *s, int ll, int rr)
	{
		l = ll;
		r = rr;

		if(l == r)
		{
			val = s[l];
			return;
		}

		tree(this, 0).init(tree, s, l, (l+r)/2);
		tree(this, 1).init(tree, s, (l+r)/2+1, r);

		val = tree(this, 0).val + tree(this, 1).val;
		return;
	}

	Value get(Tree<Cut> &tree, int ll, int rr)
	{
		if(ll == l and rr == r)
			return val;

		if(rr <= (l+r)/2)
			return tree(this, 0).get(tree, ll, rr);

		if(ll >= (l+r)/2+1)
			return tree(this, 1).get(tree, ll, rr);

		return
			tree(this, 0).get(tree, ll, (l+r)/2) +
			tree(this, 1).get(tree, (l+r)/2+1, rr);
	}
};






// end
