#ifndef TYPES_HH
#define TYPES_HH

#define nullstr ""

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

//DEFINICIONS:
typedef string str;
typedef pair<str, str> data;
typedef pair<str, data> d_elem;
typedef multimap<str, data> dictionary;

typedef vector<data> v_data;
typedef vector<d_elem> v_d_elem;
typedef vector<str> v_str;

typedef dictionary::iterator dic_ptr;
typedef pair<str, dic_ptr> r_elem;
typedef multimap<str, dic_ptr> references;
typedef references::iterator ref_ptr;

typedef pair<dic_ptr, ref_ptr> pit;
typedef map<str, pit> equivalent;
typedef equivalent::iterator equ_ptr;

//typedef map<str, str> definition;

//FUNCIONS D'INTERES GENERAL:
template<class T>
bool search(const T &s, int l, int r, const vector<T> &v, int *pos){
	if(r < l) return false;

	int half = (r+l)/2;
	if(pos) *pos =  half;
	if(v[half] == s) return true;
	if(v[half] > s) return search(s, l, half-1, v, pos);
	else return search(s, half+1, r, v, pos);
}

#endif