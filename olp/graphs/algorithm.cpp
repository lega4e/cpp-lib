/*
 * autor:   eraeg
 * date:    Jan 27 15:17:46 2020
 */

#include <queue>
#include <stack>
#include <vector>





int bfs_length(AdjacList const &adjl, int beg, int end)
{
	if(beg == end)
		return 0;

	queue<int> que;
	que.push(beg);

	vector<char> marks(adjl.n(), 0);
	marks[beg] = 1;

	int cur;
	while(!que.empty())
	{
		cur = que.front();
		for(auto b = adjl[cur].begin(), e = adjl[cur].end(); b != e; ++b)
		{
			if(*b == end)
				return marks[cur];
			if(!marks[*b])
			{
				marks[*b] = marks[cur] + 1;
				que.push(*b);
			}
		}
		que.pop();
	}

	return -1;
}

vector<int> dfs_components(AdjacList const &adjl)
{
	stack<int> vers;
	vector<int> marks(adjl.n(), 0);
	vector<int> comps;

	int c = 0;
	int v;
	for(int i = 0; i < adjl.n(); ++i)
	{
		if(marks[i])
			continue;

		marks[i] = ++c;
		comps.push_back(i);

		vers.push(i);
		while(!vers.empty())
		{
			v = vers.top();
			vers.pop();

			for(auto b = adjl[v].begin(), e = adjl[v].end(); b != e; ++b)
			{
				vers.push(*b);
				marks[*b] = c;
			}
		}
	}

	return comps;
}

void dfs(AdjacList const &adjl, int beg)
{
	vector<bool> marks(adjl.n(), false);
	stack<int> vers;
	marks[beg] = true;
	vers.push(beg);

	int v;
	while(!vers.empty())
	{
		v = vers.top();
		vers.pop();

		for(auto b = adjl[v].begin(), e = adjl[v].end(); b != e; ++b)
		{
			if(marks[*b])
				continue;

			marks[*b] = true;
			vers.push(*b);
		}
	}

	return;
}





// end
