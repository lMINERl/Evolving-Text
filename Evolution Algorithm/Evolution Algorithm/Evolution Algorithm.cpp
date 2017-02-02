// Evolution Algorithm.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include <stdint.h>
#include <iostream>
class Gen sealed{
private:
	std::string _genSTR;		// string to evolve
	std::string Target;			// goal u want to atchive
	std::string AvailableMoves; // all what u can do in this text 
	std::string Temp;			// temp storage 

	int_fast32_t fn_CalcFittness(std::string _GenSTR)const{ //calculate how many similar characters from your target
		int_fast32_t fittnessVal=(_GenSTR.length()-Target.length());
		fittnessVal=abs(fittnessVal);
		fittnessVal=(-fittnessVal); // calculate how many missing characters in other concept <calculate the distance between your current pos and your goal>
		if(fittnessVal<0){
			return fittnessVal;
		}else{
			for(uint_fast32_t i(0);i<_GenSTR.length();++i){
				if(_GenSTR[i]==Target[i]){
					fittnessVal++;
				}
			}
			return fittnessVal;
		}
	}
	void fn_DoMutation(uint_fast8_t MutationRate){   //change random index with random character per loop
		for(uint_fast8_t i(0);i<MutationRate;++i){
			Temp[rand()%(_genSTR.length())]=AvailableMoves[rand()%(AvailableMoves.length())];
		}
		//std::cout<<"dump Mutation "<<Temp<<std::endl; //show fail mutation atempts
	}
	void fn_Mutate(uint_fast8_t MutationRate){
		int_fast32_t genFittness = fn_CalcFittness(_genSTR);
		if(genFittness<0){ 
			_genSTR +=AvailableMoves[rand()%(AvailableMoves.length())]; //missing characters will be added randomly 
		}else{
			Temp.assign(_genSTR);
			fn_DoMutation(MutationRate);
			while (true){
				if(genFittness<fn_CalcFittness(Temp)){
					_genSTR.clear();
					_genSTR.assign(Temp);
					break;
				}else{
					Temp.assign(_genSTR);
					fn_DoMutation(MutationRate);
				}
			}
		}
	}
public:
	Gen(std::string Target){
		_genSTR='\0';
		Temp='\0';
		AvailableMoves=" abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ+-_}{\":;<>?/.,'[]\\|~`!@#$%^&*()";
		this->Target=Target;
	}
	void fn_Evolve() {
		if(Target!="\0"){
			while (Target.compare(_genSTR)){
				std::cout<<_genSTR<<std::endl;
				fn_Mutate(1); // Mutation << change 1 character per loop (bad implementation of mutation fn)
			}
			std::cout<<_genSTR<<std::endl;
		}
	}
};
int _tmain(int argc, _TCHAR* argv[]){
	std::string Target = "[Evolving text {Msg}] + <bad/static> implementation of mutation rate ?! - #$evolution ";
	Gen g (Target);
	g.fn_Evolve();
	std::cout<<"Finished .. ";
	getchar();
	return 0;
}

