#include "../include/parameter.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

Parameter::Parameter(const std::string& path, InputFormat format) {
	std::ifstream f(path);
	if(f.is_open()) {
		format == FI_AP? readAp(f) : readRcab(f);
		f.close();
	} else 
		errorMessage("Opening file");
}

void Parameter::readAp(std::ifstream& fin) {
	if(fin >> _n) {
		//std::cout << _n << std::endl;
		double x,y,d,w;
		std::vector<double> xs,ys;
		_wij = std::vector<std::vector<double> >(_n);
		_cij = std::vector<std::vector<double> >(_n);

		//Reading coordinates
		for (int i = 0; i < _n; ++i) {
			if(fin >> x >> y) {
				//std::cout << std::setprecision(12) << x << " " << y << std::endl;
				xs.push_back(x);	
				ys.push_back(y);
			} else 
			    errorMessage("Not enough coordinates");
		}

		//Calculating distances
		for (int i = 0; i < _n ; ++i) 
			for (int j = 0; j < _n ; ++j) {
				//d = std::sqrt(std::pow(xs[i]-xs[j],2)+std::pow(ys[i]-ys[j],2));
				_cij[i].push_back(d);
			}
		
		//Reading flows
		for (int i = 0; i < _n ; ++i) { 
			for (int j = 0; j < _n ; ++j) {
			    if(fin >> w) {
					//std::cout << w << " ";
					_wij[i].push_back(w);
				}
				else	
					errorMessage("Not enough fows");	
			}
			std::cout << std::endl;
		}

		//Reading prices, aplha and cost of establishing 	
		if(fin >> _c >> _alpha >> _d) {
			//std::cout << _c << std::endl;
			//std::cout << _alpha << std::endl;
			//std::cout << _d << std::endl;
			for(int i = 0; i < _n ; ++i) 
				if(fin >> d) {
					_fi.push_back(d);
				//	std::cout << d << std::endl;
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
		//std::cout << _n << std::endl;
		double k,m,w,c;
		_wij = std::vector<std::vector<double> >(_n);
		_cij = std::vector<std::vector<double> >(_n);

		//Reading flows and costs
		for(int i = 0; i < _n ; ++i) {
			for(int j = 0; j < _n ; ++j) {
			   if(fin >> k >> m >> w >> c) {
				//    std::cout << k << " " << m << " ";
				//	std::cout << w << " " << c << std::endl;
					_wij[i].push_back(w);
					_cij[i].push_back(c);
			   } else
				   errorMessage("Not enough lines with flows and costs");
			}
		}

		//Reading cost of establishing
		for (int i = 0; i < _n ; ++i) {
			if(fin >> k) {
				//std::cout << k << std::endl;
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
