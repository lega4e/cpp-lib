#ifndef NVX_LAYER_IFSTREAM_HPP_892302
#define NVX_LAYER_IFSTREAM_HPP_892302

#include <iostream>
#include <fstream>
#include <stack>





namespace nvx
{





class LayerIfstream: public std::ifstream
{
public:
	// core
	LayerIfstream(
		bool usecin = false,
		bool autoclose = false
	);
	LayerIfstream(
		std::string const &filename,
		bool usecin = false,
		bool autoclose = false
	);

	bool open(std::string const &file);
	void close();

	std::string curfile() const;



	// properties
	bool usecin() const;
	void usecin(bool is);

	bool autoclose() const;
	void autoclose(bool is);

	bool empty() const;
	int depth() const;



	// input
	int get();
	void unget();

	template<typename T> 
	LayerIfstream &operator>>(T &val)
	{
		while(!empty())
		{
			(std::ifstream &)(*this) >> val;
			if(eof() && autoclose_)
				close();
			else
				return *this;
		}

		if(usecin_)
			std::cin >> val,
			setstate(std::cin.rdstate());

		return *this;
	}



private:
	bool usecin_, autoclose_;
	std::stack<std::string> files;
	std::stack<int> poses;

};





// free
LayerIfstream &getline(
	LayerIfstream &fin,
	std::string &s
);

LayerIfstream &getline(
	LayerIfstream &fin,
	std::string &s,
	char delim
);





}





#endif
