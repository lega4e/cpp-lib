#ifndef NVX_SORT_QUEUE_HPP
#define NVX_SORT_QUEUE_HPP

#include <functional>
#include <unordered_map>
#include <vector>





namespace nvx
{





template<typename OperandType>
struct SortQueue
{
	// types
	typedef OperandType operand_type;
	typedef std::function<
		bool(operand_type const &, operand_type const &)
	> cmp_type;



	// members
	/*
	 * Заполните вектор компараторами, которые будут
	 * применяться в соответствии с их порядком в
	 * векторе
	 */
	std::vector<cmp_type> cmps;



	// methods
	/*
	 * Оператор, чтобы добавлять новые компараторы
	 * в структуру
	 */
	SortQueue &operator<<(cmp_type const &cmp)
	{
		cmps.push_back(cmp);
		return *this;
	}

	/*
	 * Вызовите этот метод, чтобы сравнить с помощью
	 * очереди компараторов два операнда
	 */
	bool operator()(
		operand_type const &lhs,
		operand_type const &rhs
	) const
	{
		for(auto b = cmps.begin(), e = cmps.end(); b != e; ++b)
		{
			if((*b)(lhs, rhs))
				return true;

			if((*b)(rhs, lhs))
				return false;
		}
				
		return false;
	}

};





template<typename OperandType, typename KeyType = char>
struct SortQueueCreator
{
	// types
	typedef OperandType operand_type;
	typedef KeyType key_type;
	typedef std::function<
		bool(operand_type const &, operand_type const &)
	> cmp_type;
	typedef SortQueue<OperandType> sort_type;

	

	// members
	std::unordered_map<key_type, cmp_type> cmps;




	// methods
	/*
	 * Методы для добавления новых компараторов вместе с ключом
	 */
	inline SortQueueCreator &push(KeyType key, cmp_type const &cmp)
	{
		cmps[key] = cmp;
		return *this;
	}

	inline SortQueueCreator &push(std::pair<key_type, cmp_type> const &p)
	{
		cmps[p.first] = p.second;
		return *this;
	}



	/*
	 * Добавив все компараторы, можно вызвать этот мотедо, который
	 * создаст соответствующую переданной последовательности ключей
	 * очередь сортировки
	 */
	sort_type operator()(std::vector<key_type> const &keys) const
	{
		sort_type sorting;
		for(auto b = keys.begin(), e = keys.end(); b != e; ++b)
			sorting.cmps.push_back(cmps.find(*b)->second);
		return sorting;
	}

	sort_type operator()(std::string const &keys)
	{
		sort_type sorting;
		for(auto b = keys.begin(), e = keys.end(); b != e; ++b)
			sorting << (cmps[*b]);
		return sorting;
	}



};





}





#endif // NVX_SORT_QUEUE_HPP
