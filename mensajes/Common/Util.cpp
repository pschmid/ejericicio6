#include "Util.h"

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

string Util::itoa(int number){
	 string numberString;
	 stringstream conversor;
	 conversor << number;
	 numberString = conversor.str();
	 return numberString;
}

vector<string> Util::split(string cadena , char separator){
	vector<string> resultado;
	size_t encontrado;
	int inicio = 0;
	encontrado=cadena.find_first_of(separator);
	while (encontrado != string::npos) {
		string termino = cadena.substr(inicio,encontrado - inicio);
		if (termino.size()) {
			resultado.push_back(termino);
		}
	    inicio = encontrado + 1;
	    encontrado = cadena.find_first_of(separator,encontrado+1);
	}
	// Agregar el ultimo
	string termino = cadena.substr(inicio);
	if (termino.size()) {
		resultado.push_back(termino);
	}
	return resultado;
}

string Util::toLower(string cadena){
	string lowercase("");
	for(int i=0; i < (int)cadena.size(); i++) {
		lowercase += (char) tolower(cadena[i]);
	}
	return lowercase;
}

string Util::ltrim(const string &s) {
	string trimmed(s);
	trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return trimmed;
}

string Util::rtrim(const string &s) {
	string trimmed(s);
	trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), trimmed.end());
	return trimmed;
}

string Util::trim(const string &s) {
	return ltrim(rtrim(s));
}
