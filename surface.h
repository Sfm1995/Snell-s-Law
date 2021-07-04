#pragma once
#include<iostream>
#include<vector>
using namespace std;

class surface {
private:
	vector<double> p = { 0,0,0 };
	vector<double> n = { 0,0,1 };
	double n_water = 1.3330;
	double n_ice = 1.306;
	double n_air = 1;
	double n_metal = 0.05;
	double n_1=1;
	double n_2=1;
public:
	vector<double> get_p() {
		return p;
	}
	void set_p(vector<double> pa) {
		p = pa;
	}
	vector<double> get_n() {
		return n;
	}
	void set_n(vector<double> na) {
		n = na;
	}
	double get_n_water() {
		return n_water;
	}
	double get_n_ice() {
		return n_ice;
	}
	double get_n_air() {
		return n_air;
	}
	double get_n_metal() {
		return n_metal;
	}
	double get_n_1() {
		return n_1;
	}
	void set_n_1(double n_1a) {
		n_1 = n_1a;
	}
	double get_n_2() {
		return n_2;
	}
	void set_n_2(double n_2a) {
		n_2 = n_2a;
	}

};