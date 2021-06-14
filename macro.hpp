#ifndef NVX_MACRO_7429302873
#define NVX_MACRO_7429302873

#include <exception>





#define TRY try {

#define CATCH \
	} \
	catch(std::string const &e) \
	{ \
		std::cerr << "Error: " << e << endl; \
	} \
	catch(char const *e) \
	{ \
		std::cerr << "Error: " << e << endl; \
	} \
	catch(std::exception const &e) \
	{ \
		std::cerr << "Error: " << e.what() << endl; \
	}





#define ARG(...) __VA_ARGS__





#endif
