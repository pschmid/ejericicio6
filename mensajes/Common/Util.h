#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <ctype.h>
#include <cctype>
#include <algorithm>
#include <functional>
#include <locale>

using namespace std;

class Util {
public:
	Util();
	virtual ~Util();
	static string itoa(int number);
	static vector<string> split(string cadena,char separator);
	static string toLower(string s);
	static string ltrim(const string& s);
	static string rtrim(const string& s);
	static string trim(const string& s);
};

#endif /* UTIL_H_ */
