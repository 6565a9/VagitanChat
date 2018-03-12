#include<string.h>
#include<string>

//#define MAXSIZETMP (1<<sizeof(int)*8) ... count of / 10/ 10/ 10/ 10 10
#define MAXSIZETMP 64


char * toSys(long long int from, unsigned char sys){
	char * tmp = new char[MAXSIZETMP];
	void * f = (char*)tmp;
	unsigned char mod;
	while(from){
		mod = (from%sys);
		if(mod >= 10)
			*(tmp)= 55 + mod;
		else
			*(tmp)= '0' + mod;
		from/=sys;
		tmp++;
	}tmp--;


	char * returns = new char[strlen(tmp)+3];
	void * f1 = (char*)returns;

	while(tmp >= f)
		*(returns++)=*(tmp--);
	delete [] (char*)f;
	return (char*)f1;
}

std::string toNotation(long long int from, unsigned char sys){
	char * tmp = toSys(from, sys);
	std::string returns = tmp;
	delete [] tmp;
	return returns;
}


int main(void){
	auto str = toNotation(123, 16);
}
