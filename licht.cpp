#include<iostream>
#include<vector>
using namespace std;



class licht {
private:
	vector<double> s = { 0,0,0 };
	vector<double> v = { 0,0,1 };
	vector<double> t = { 0,1,2,3,4,5,6,7,8,9,10 };
	vector<vector<double> > l = { {0,0,0},{0,0,1},{0,0,2},{0,0,3},{0,0,4},{0,0,5},{0,0,6},{0,0,7},{0,0,8},{0,0,9},{0,0,10} };
public:
	vector<double> get_s() {
		return s;
	}
	void set_s(vector<double> sa) {
		s = sa;
		set_l(vector_tran(s, v, t));
	}
	vector<double> get_v() {
		return v;
	}
	void set_v(vector<double> va) {
		v = va;
		set_l(vector_tran(s, v, t));
	}
	vector<double> get_t() {
		return t;
	}
	void set_t(vector<double> ta) {
		t = ta;
		set_l(vector_tran(s, v, t));
	}
	vector<vector<double> > get_l() {
		return l;
	}
	void set_l(vector<vector<double> > la) {
		l = la;
	}
	vector<double> get_licht_in_t0(licht Licht, double t) {
		vector<double> mp = { 0,0,0 };
		for (int i = 0; i < Licht.s.size(); i++) {
			mp[i] = Licht.s[i] + t * Licht.v[i];
		}
		return mp;

	}
	vector<vector<double> >  vector_tran(vector<double> s, vector<double> v, vector<double> t) {
		vector<vector<double> > l(t.size(), vector<double>(v.size()));
		for (size_t i_1 = 0; i_1 < t.size(); i_1++) {
			for (size_t j_1 = 0; j_1 < v.size(); j_1++) {
				l[i_1][j_1] = v[j_1] * t[i_1] + s[j_1];
			}
		}
		return l;
	}
};
