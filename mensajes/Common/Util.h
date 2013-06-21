#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <ctype.h>

using namespace std;

class Util {
public:
	Util();
	virtual ~Util();
	static string itoa(int number);
	static vector<string> split(string cadena,char separator);
	static string toLower(string s);
};

#endif /* UTIL_H_ */
