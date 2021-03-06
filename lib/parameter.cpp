#include "../include/parameter.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

Parameter::Parameter(const std::string& path, InputFormat form) : format(form) {
	std::ifstream f(path);
	if(f.is_open()) {
		form == FI_AP? readAp(f) : readRcab(f);
		f.close();
	} else 
		errorMessage("Opening file");
}

void Parameter::readAp(std::ifstream& fin) {
	if(fin >> _n) {
		double x,y,d,w;
		std::vector<double> xs,ys;
		_wij = std::vector<std::vector<double> >(_n);
		_cij = std::vector<std::vector<double> >(_n);

		//Reading coordinates
		for (int i = 0; i < _n; ++i) {
			if(fin >> x >> y) {
				xs.push_back(x);	
				ys.push_back(y);
			} else 
			    errorMessage("Not enough coordinates");
		}

		//Calculating distances
		for (int i = 0; i < _n ; ++i) 
			for (int j = 0; j < _n ; ++j) {
				_cij[i].push_back(d);
			}
		
		//Reading flows
		for (int i = 0; i < _n ; ++i) { 
			for (int j = 0; j < _n ; ++j) {
			    if(fin >> w) {
					_wij[i].push_back(w);
				}
				else	
					errorMessage("Not enough fows");	
			}
		}

		//Reading prices, aplha and cost of establishing 	
		if(fin >> _c >> _alpha >> _d) {
			for(int i = 0; i < _n ; ++i) 
				if(fin >> d) {
					_fi.push_back(d);
				}
				else
					errorMessage("Not enough establishing costs");
		} else
			errorMessage("Not entered alpha and costs");	
	} else
		errorMessage("File must start with n");
}

void Parameter::readRcab(std::ifstream& fin) {
    if(fin >> _n >> _alpha) {
		double k,m,w,c;
		_wij = std::vector<std::vector<double> >(_n);
		_cij = std::vector<std::vector<double> >(_n);

		//Reading flows and costs
		for(int i = 0; i < _n ; ++i) {
			for(int j = 0; j < _n ; ++j) {
			   if(fin >> k >> m >> w >> c) {
					_wij[i].push_back(w);
					_cij[i].push_back(c);
			   } else
				   errorMessage("Not enough lines with flows and costs");
			}
		}

		//Reading cost of establishing
		for (int i = 0; i < _n ; ++i) {
			if(fin >> k) {
				_fi.push_back(k);
			}
		    else
				errorMessage("Not enoush establishing costs");	
		} 
	} else
		errorMessage("File must start with n and alpha");
}

void Parameter::errorMessage(const std::string& msg) const {
	std::cerr << "Error: " << msg << std::endl;
	std::exit(1);
}
