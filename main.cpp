#include"matplotlibcpp.h"     //from github matplotlib-cpp https://github.com/lava/matplotlib-cpp#readme to get image;
#include<iostream>
#include<vector>
#include <cmath>
#include "licht.h"
#include "surface.h"

using namespace std;
namespace plt = matplotlibcpp;


double  dot(vector<double> v, vector<double> t);
vector<double> cross(vector<double> a, vector<double> b);
vector<double>  vect(vector<double> a, vector<double> b);
vector<double> get_mp_t_0(licht Licht, surface Surface);
licht refraction(licht Licht, surface Surface);
licht reflection(licht Licht, surface Surface);
void lichtplot(surface Surface, licht Licht);

int main() {
	
	
	
	licht Licht;
	surface Surface;
	
	//normal
	
	Licht.set_s({ 0,-10,-10 });
	Licht.set_v({ 0,10,10 });
	Surface.set_n({ 0,0,1 });
	Surface.set_p({ 0,0,0 });
	Surface.set_n_1(2);
	Surface.set_n_2(1);
    
	

	//parallel
	/*
	Licht.set_s({ 1,1,1 });
	Licht.set_v({ 1,1,0 });
	Surface.set_n({ 0,0,1 });
	Surface.set_p({ 0,0,0 });
	Surface.set_n_1(2);
	Surface.set_n_2(1);
    */

	//No refraction
    /*
	Licht.set_s({ 0,-10,1 });
	Licht.set_v({ 0,10,-1 });
	Surface.set_n({ 0,0,1 });
	Surface.set_p({ 0,0,0 });
	Surface.set_n_1(2);
	Surface.set_n_2(1);
     */


	//vertical
	/*
	Licht.set_s({ 0,0,1 });
	Licht.set_v({ 0,0,-1 });
	Surface.set_n({ 0,0,1 });
	Surface.set_p({ 0,0,0 });
	Surface.set_n_1(2);
	Surface.set_n_2(1);
     */

	//Light source on the surface
	/*
    Licht.set_s({ 0,0,0 });
	Licht.set_v({ 0,-1,-1 });
	Surface.set_n({ 0,0,1 });
	Surface.set_p({ 0,0,0 });
	Surface.set_n_1(2);
	Surface.set_n_2(1);
	*/
	

	//Only light source without light vector
    /*
	Licht.set_s({ 0,0,1 });
	Licht.set_v({ 0,0,0});
	Surface.set_n({ 0,0,1 });
	Surface.set_p({ 0,0,0 });
	Surface.set_n_1(2);
	Surface.set_n_2(1);
   */
	//The light is almost perpendicular to the plane
	/*
	Licht.set_s({ 0,-1,150000 });
	Licht.set_v({ 0,1,-150000 });
	Surface.set_n({ 0,0,1 });
	Surface.set_p({ 0,0,0 });
	Surface.set_n_1(2);
	Surface.set_n_2(1);
    */
	lichtplot(Surface, Licht);





	return 0;
}

//Dot product
double dot(vector<double> v, vector<double> t) {
	double sum = 0;
	for (size_t i = 0; i < t.size(); i++) {
		sum = sum + v[i] * t[i];
	}
	return sum;
}
//Cross product
vector<double> cross(vector<double> a, vector<double> b) {
	vector<double> c = { 0,0,0 };
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	return c;
}

//Calculate the vector between two points a and b
vector<double>  vect(vector<double> a, vector<double> b) {
	vector<double> vec = { 0,0,0 };
	for (size_t i = 0; i < a.size(); i++) {
		for (size_t j = 0; j < b.size(); j++) {
			if (i == j) {
				vec[i] = b[j] - a[i];
			}

		}
	}
	return vec;
}

//Vector unitization
vector<double>  uniti(vector<double> a) {
	vector<double> b = { 0,0,0 };
	for (size_t i = 0; i < a.size(); i++) {
		b[i] = a[i] / sqrt(dot(a, a));
	}
	return b;
}




//Get the intersection of the light and the plane and the time t0 (in order to get the light)
vector<double> get_mp_t_0(licht Licht, surface Surface) {
	vector<double> mp_t_0 = { 0,0,0,0 };
	double x = 0;
	double y = 0;
	double z = 0;
	double t_0 = 0;
	vector<double> n = Surface.get_n();
	vector<double> p = Surface.get_p();
	vector<double> v = Licht.get_v();
	vector<double> s = Licht.get_s();
	if (dot(n, v) == 0) {
		mp_t_0 = { 0,0,0,0 };         
	}
	else if (dot(vect(s, p), n) == 0) {    
		mp_t_0 = { s[0],s[1],s[2],0 };

	}
	else {                           
		t_0=-(n[0]*(s[0]-p[0])+n[1]*(s[1]-p[1])+n[2]*(s[2]-p[2]))/(n[0]*v[0]+n[1]*v[1]+n[2]*v[2]);
		x=s[0]+v[0]*t_0;
		y=s[1]+v[1]*t_0;
		z=s[2]+v[2]*t_0;
		mp_t_0 = { x,y,z,t_0 };
	}


	return mp_t_0;
}

//In order to get refracted light
licht refraction(licht Licht, surface Surface) {
	licht Licht_refra;
	vector<double> n = Surface.get_n();
	vector<double> v_1 = Licht.get_v();
	vector<double> v_1_uniti = uniti(v_1);
	double i_1 = 0;
	for (size_t i = 0; i < v_1.size(); i++) {
		if (v_1[i] != 0) {
			i_1 = v_1[i]/v_1_uniti[i]  ;
		}
	}
	vector<double> v_r = { 0,0,0 };
	vector<double> t_0 = { 0,1,2,3,4,5,6,7,8,9,10 };
	double n_1;
	double n_2;
	if (dot(n, v_1) < 0) {
		n_1 = Surface.get_n_1();
		n_2 = Surface.get_n_2();
	}
	else {
		n_1 = Surface.get_n_2();
		n_2 = Surface.get_n_1();
		for (size_t i = 0; i < n.size(); i++) {
			n[i] = -n[i];
		}
	}
	vector<double> mp_t_0 = get_mp_t_0(Licht, Surface);
	Licht_refra.set_s({ mp_t_0[0],mp_t_0[1], mp_t_0[2] });


	for (size_t d = 0; d < t_0.size(); d++) {
		
		t_0[d] = i_1*mp_t_0[3] / 10 * d;
		
	}
	Licht_refra.set_t(t_0);

	long double cos_1 = -dot(n, v_1) / sqrt((dot(n, n)) * dot(v_1, v_1));
	long double sin_1 = sqrt(1 - cos_1 * cos_1);
	long double sin_2 = n_1 / n_2 * sin_1;
	long double cos_2 = sqrt(1 - sin_2 * sin_2);
	long double sin_2max = 1;
	long double sin_1max = n_2 * sin_2max / n_1;
	//cout << cos_1 << " " << cos_2 << " " << sin_1 << " " << sin_2 << " ";
	vector<double> l = { 0,0,0 };
	vector<double> AO = vect(Licht.get_s(), Licht_refra.get_s());
	n = uniti(n);
	AO = uniti(AO);

	if (cross(n, v_1) == l) {
		v_r = v_1;
	}
	else if ((n_1 >= n_2) && (sin_1 > sin_1max)) {
		v_r = { 0,0,0 };
	}



	else {
		for (size_t q = 0; q < v_r.size(); q++) {
			v_r[q] = (n_1 / n_2 * cos_1 - cos_2) * n[q] + n_1 / n_2 * AO[q];
			//cout << v_r[q] << " ";
		}


	}
	Licht_refra.set_v(v_r);
	return Licht_refra;
}


//In order to get the reflected light
licht reflection(licht Licht, surface Surface) {
	licht Licht_refle;
	vector<double> n = Surface.get_n();
	vector<double> v_1 = Licht.get_v();
	vector<double> v_r = { 0,0,0 };
	vector<double> mp_t_0 = get_mp_t_0(Licht, Surface);
	vector<double> t_0 = { 0,1,2,3,4,5,6,7,8,9,10 };
	Licht_refle.set_s({ mp_t_0[0],mp_t_0[1], mp_t_0[2] });
	for (size_t d = 0; d < t_0.size(); d++) {
		t_0[d] = mp_t_0[3] / 10 * d;
	}
	Licht_refle.set_t(t_0);
	if (dot(n, v_1) < 0) {
		for (size_t i = 0; i < n.size(); i++) {
			n[i] = n[i];
		}
	}
	else {
		for (size_t i = 0; i < n.size(); i++) {
			n[i] = -n[i];
		}
	}
	vector<double> AO = vect(Licht.get_s(), Licht_refle.get_s());
	for (size_t i = 0; i < v_r.size(); i++) {
		v_r[i] = -2 * (dot(AO, uniti(n))) * n[i] + AO[i];
	}
	Licht_refle.set_v(v_r);
	return Licht_refle;
}

//To get the image of the result
void lichtplot(surface Surface , licht Licht ){
	vector<double> mp_t0 = get_mp_t_0(Licht, Surface);
	vector<double> n = Surface.get_n();
	
	licht Licht_le=reflection(Licht, Surface);
	licht Licht_ra = refraction(Licht, Surface);
	vector<vector<double>> le_l = Licht_le.get_l();
	vector<vector<double>> ra_l = Licht_ra.get_l();
	vector<double> t = { 0,1,2,3,4,5,6,7,8,9,10 };
	if(mp_t0[3]!=0){
	for (int i = 0; i <= 10; i++) {
		t[i] = mp_t0[3] / 10 * i;
	}
	Licht.set_t(t);
	}
	vector<vector<double>> licht_l = Licht.get_l();
	
	std::vector<std::vector<double>> x, y, z;
	for (double i = -5; i <= 5; i += 0.25) {
		std::vector<double> x_row, y_row, z_row;
		for (double j = -5; j <= 5; j += 0.25) {
			if (n[2] != 0) {
				x_row.push_back(i + mp_t0[0]);
				y_row.push_back(j + mp_t0[1]);
				z_row.push_back((i * n[0] + j * n[1] - mp_t0[2] * n[2]) / (-n[2]));
			}
			else if (n[1] != 0) {
				x_row.push_back(i + mp_t0[0]);
				z_row.push_back(j + mp_t0[2]);
				y_row.push_back((i * n[0] + j * n[2] - mp_t0[1] * n[1]) / (-n[1]));

			}
			else {
				y_row.push_back(i + mp_t0[1]);
				z_row.push_back(j + mp_t0[2]);
				x_row.push_back((i * n[1] + j * n[2] - mp_t0[0] * n[0]) / (-n[0]));

			}
			
		}
		x.push_back(x_row);
		y.push_back(y_row);
		z.push_back(z_row);
	}

	
	std::vector<double> x_row_le, y_row_le, z_row_le;	
	for (size_t i = 0; i < le_l.size(); i++) {

		for (size_t j = 0; j < le_l[i].size(); j++) {
			if (j == 0) {
				x_row_le.push_back(le_l[i][j]);
			}
			else if (j == 1) {
				y_row_le.push_back(le_l[i][j]);
			}
			else {
				z_row_le.push_back(le_l[i][j]);
			}

		}

	}
	
	
	

	std::vector<double> x_row_ra, y_row_ra, z_row_ra;
	for (size_t i = 0; i < ra_l.size(); i++) {

		for (size_t j = 0; j < ra_l[i].size(); j++) {
			if (j == 0) {
				x_row_ra.push_back(ra_l[i][j]);
			}
			else if (j == 1) {
				y_row_ra.push_back(ra_l[i][j]);
			}
			else {
				z_row_ra.push_back(ra_l[i][j]);
			}

		}

	}
	
	std::vector<double> x_row_l, y_row_l, z_row_l;
	for (size_t i = 0; i < licht_l.size(); i++) {

		for (size_t j = 0; j < licht_l[i].size(); j++) {
			if (j == 0) {
				x_row_l.push_back(licht_l[i][j]);
			}
			else if (j == 1) {
				y_row_l.push_back(licht_l[i][j]);
			}
			else {
				z_row_l.push_back(licht_l[i][j]);
			}

		}

	}

	long i_2 = 1;
	plt::figure;
	plt::plot_surface(x, y, z,i_2);                    //Get an image of the surface
	plt::plot3(x_row_le, y_row_le, z_row_le,i_2);     //Get the image of the reflected light
	plt::plot3(x_row_ra, y_row_ra, z_row_ra, i_2);   //Get an image of refracted light
	plt::plot3(x_row_l, y_row_l, z_row_l,i_2);    //Get an image of the incident light

	plt::show();
	
	  
}

