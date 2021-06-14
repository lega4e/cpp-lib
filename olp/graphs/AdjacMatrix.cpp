/*
 * autor:   quix
 * date:    Jan 26 17:00:45 2020
 */

#include <cstring>





/*
 * ----- ДОГОВОРЁННОСТИ
 * При вводе через файл матрица смежности вседа должена быть очищенна,
 * автоматически ничего не делается
 *
 *
 *
 * ----- СОЗДАНИЕ, КОНВЕРТАЦИЯ
 * Методы
 *    * init......выделяет память для массива, где хранятся элементы
 *    * zeroize...ставит все элементы матрицы по нулям
 *    * free......освобождает память, выделенную под элементы
 *
 *
 *
 * ----- ОПЕРАТОРЫ
 *    * [i] (const) — даёт доступ к строке (используйте [i][j])
 *
 *
 *
 * ----- ДРУГОЕ
 *    <fun_name>1 — означает, что эта функция работает точно так же,
 *    как <fun_name>, но в ней считается, что вершины нумеруются,
 *    начиная с единицы, а не с нуля
 *
 *    * scan............считывает сначала порядок матрицы, затем все
 *                      элементы; 
 *    * scannon.........сразу считывает все элемены; память для массива
 *                      должна быть выделенна заранее
 *    * scan_riblist....читает из файла сначала два числа: кол-во вершин и
 *                      кол-во рёбер — затем считывает сами рёбра,
 *                      представленные парой чисел — номерами вершин;
 *                      вторым аргументом функции идёт указание, считать
 *                      ли граф ориентированным (по умолчанию считается
 *                      неориентированным)
 *    * scan_riblist1...см. выше
 *    * print...........выводит в том же формате, в каком считывает
 *                      в функции scan
 *
 *
 *
 */

template<typename T>
struct AdjacMatrix_template
{
	// types
	typedef T value_type;


	// data-member
	int n;
	value_type *d;



	// base
	inline AdjacMatrix_template &init()
	{
		d = new value_type[n*n];
		return *this;
	}

	inline AdjacMatrix_template &init(int newn)
	{
		n = newn;
		d = new value_type[n*n];
		return *this;
	}

	inline AdjacMatrix_template &zeroize()
	{
		memset(d, 0, sizeof(value_type)*n*n);
		return *this;
	}

	inline AdjacMatrix_template &free()
	{
		delete[] d;
		return *this;
	}



	// at
	inline value_type *operator[](int i)
	{
		return d + i*n;
	}

	inline const value_type *operator[](int i) const
	{
		return d + i*n;
	}
	
	
	
	// input, output
	inline AdjacMatrix_template &scan(FILE *file = stdin)
	{
		fscanf(file, "%i", &n);
		init();
		scannon(file);
		return *this;
	}
	
	AdjacMatrix_template &scannon(FILE *file = stdin)
	{
		int input;
		for(auto *b = d, *e = d+n*n; b != e; ++b)
			fscanf(file, "%i", &input),
			*b = input;
		return *this;
	}

	AdjacMatrix_template &scan_riblist(FILE *file = stdin, bool oriented = false)
	{
		int m;
		fscanf(file, "%i%i", &n, &m);
		init();
		zeroize();

		int first, second;
		for(int i = 0; i < m; ++i)
		{
			fscanf(file, "%i%i", &first, &second);
			d[ n*first + second ] = 1;

			if(!oriented)
				d[ n*second + first ] = 1;
		}

		return *this;
	}

	AdjacMatrix_template &scan_riblist1(FILE *file = stdin, bool oriented = false)
	{
		int m;
		fscanf(file, "%i%i", &n, &m);
		init();
		zeroize();

		int first, second;
		for(int i = 0; i < m; ++i)
		{
			fscanf(file, "%i%i", &first, &second);
			--first, --second;
			d[ n*first + second ] = 1;

			if(!oriented)
				d[ n*second + first ] = 1;
		}

		return *this;
	}

	void print(FILE *file = stdout) const
	{
		fprintf(file, "%i\n", n);
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				fprintf(file, "%i ", (int)d[i*n + j]);
			}
			fprintf(file, "\n");
		}
		return;
	}


	
};





// typedefs
typedef AdjacMatrix_template<char> AdjacMatrix;
typedef AdjacMatrix_template<char> AdjacMatrixC;
typedef AdjacMatrix_template<int> AdjacMatrixI;
typedef AdjacMatrix_template<long long> AdjacMatrixLL;
typedef AdjacMatrix_template<float> AdjacMatrixF;
typedef AdjacMatrix_template<double> AdjacMatrixD;
typedef AdjacMatrix_template<long double> AdjacMatrixLD;





// end
