#include "LayerIfstream.hpp"

#include <iostream>


using namespace std;





namespace nvx
{





// core
LayerIfstream::LayerIfstream(
	bool usecin,
	bool autoclose
):
	usecin_(usecin),
	autoclose_(autoclose) {}

LayerIfstream::LayerIfstream(
	string const &filename,
	bool usecin,
	bool autoclose
):
	usecin_(usecin),
	autoclose_(autoclose)
{
	open(filename);
	return;
}



bool LayerIfstream::open( string const &file )
{
	if(is_open())
	{
		int pos = tellg();
		poses.push(pos);
	}

	ifstream::close();
	ifstream::open(file);
	if(!is_open())
	{
		if(!files.empty())
		{
			ifstream::open(files.top());
			seekg(poses.top());
			poses.pop();
		}
		return false;
	}

	files.push(file);

	return true;
}

void LayerIfstream::close()
{
	if(is_open())
	{
		ifstream::close();
		files.pop();
	}

	if(!files.empty())
	{
		ifstream::open(files.top());
		seekg(poses.top());
		poses.pop();
	}
	else if(usecin_)
		clear(cin.rdstate());
	else
		setstate(ios::eofbit);
	return;
}

std::string LayerIfstream::curfile() const
{
	if(files.empty())
		return "";
	else
		return files.top();
}





// properties
bool LayerIfstream::usecin() const
{
	return usecin_;
}

void LayerIfstream::usecin(bool is)
{
	usecin_ = is;
	return;
}



bool LayerIfstream::autoclose() const
{
	return autoclose_;
}

void LayerIfstream::autoclose(bool is)
{
	autoclose_ = is;
	return;
}



bool LayerIfstream::empty() const
{
	return files.empty();
}

int LayerIfstream::depth() const
{
	return files.size();
}





int LayerIfstream::get()
{
	while(is_open())
	{
		int ch = ifstream::get();

		if(!eof())
			return ch;

		if(autoclose_)
			close();
		else
			return EOF;
	}

	if(usecin_)
	{
		int ch = cin.get();
		clear(cin.rdstate());
		return ch;
	}

	return EOF;
}

void LayerIfstream::unget()
{
	if(is_open())
		ifstream::unget();
	else if(usecin_)
		cin.unget();
	else
		throw logic_error("call unget but not is_open and not usecin_");
	return;
}





// free
LayerIfstream &getline(
	LayerIfstream &fin,
	string &s
)
{
	while(!fin.empty())
	{
		getline( (ifstream &)fin, s );
		if(!fin.eof())
			return fin;

		if(fin.autoclose())
			fin.close();
		else
			return fin;
	}

	if(fin.usecin())
	{
		getline(cin, s);
		fin.clear(cin.rdstate());
	}
	else
	{
		fin.setstate(ios::eofbit);
	}

	return fin;
}

LayerIfstream &getline(
	LayerIfstream &fin,
	string &s,
	char delim
);





}





// end
