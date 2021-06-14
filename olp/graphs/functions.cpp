/*
 * autor:   quix
 * date:    Jan 26 17:50:01 2020
 */





/*
 * Конвертирует матрицу смежности в список смежности;
 * список смежности должен быть чист перед вызовом
 * функции
 */
void conv(AdjacMatrix const &adjm, AdjacList &adjl)
{
	adjl.ribs.resize(adjm.n);
	for(int i = 0; i < adjm.n; ++i)
	{
		for(int j = 0; j < adjm.n; ++j)
		{
			if(adjm[i][j])
				adjl[i].push_back(j);
		}
	}
	return;
}



/*
 * Преобразует список смежности в матрицу смежности;
 * матрица должна быть пустой, без выделенной памяти
 * перед вызовом функции
 */
void conv(AdjacList const &adjl, AdjacMatrix &adjm)
{
	adjm.init( adjl.n() ).zeroize();
	for(int i = 0; i < adjl.n(); ++i)
	{
		for(auto b = adjl[i].begin(), e = adjl[i].end(); b != e; ++b)
			adjm[i][*b] = 1;
	}
	return;
}





// end
