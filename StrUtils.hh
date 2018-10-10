#ifndef STRUTILS_HH
#define STRUTILS_HH

bool isC0(const str &s){
	return s == C0;
}

bool isC1(const str &s){
	return s == C1;
}

bool isC2(const str &s){
	return s == C2;
}

bool isC3(const str &s){
	return s == C3;
}

bool isC2C3(const str &s){
	if(s == C2 or s == C3) return true;
	return false;
}

bool isDefDict(const str &s){
	return s == defDict;
}

void errOut(const str &s, const str &E_a, const str &E_b, bool b){
	cout << tag[3] << s;
	if(b) cout << E_a << endl;
	else cout << E_b << endl;
}

bool C0Err(const str &s, bool b){
	errOut(s, E12, E11, b);
	return false;
}

bool C2C3Err(const str &s, bool b){
	errOut(s, E18, E17, b);
	return false;
}

void print(int i, char c){
	for(; i > 0; i--) cout << c;
}

void space(int i){
	print(i, ' ');
}

void RARInfo(const str &s){
/*Imprimeix s en el RAR*/
	cout << LGreen << s;
	cout << U0 << usr;
}

void RAFInfo(const str &s, const int &i){
/*Imprimeix s en el RAF, segons convingui*/
	cout << tag[4];
	if(not i) cout << s;
}

void RATInfo(const data &l, bool b){
	cout << tag[4] << LBlue;
	if(not b) cout << l.first;
	else cout << l.second;
	cout << ": " << Default;
}

void WordLang(const str &s,
			  const data &l,
			  bool b){
/*Escriu el llenguatge i la paraula*/
	
	cout << LBlue << U1;
	if(not b) cout << l.first;
	else cout << l.second;
	cout << U2 << Default;
	
	if(not b) space(9-l.first.size());
	else space(9-l.second.size());
	cout << s << endl;
}

bool Ask(const str &cmd, const str &s){
	cout << tag[1] << cmd << s << endl;
	cout << tag[2] << Q0;
	
	str answer{nullstr};
	cin >> answer;
	cin.ignore();
	
	return answer == A0;

}

bool Warning(bool b,
			 const str &C,
			 const str &W,
			 const str &E){
	if(b) cout << tag[0] << C << W << endl;
	else cout << tag[3] << C << E << endl;
	return b;
}

void cslInfo(){
	cout << I0 << endl;
	cout << I1 << endl;
	cout << endl;
}

void colorize(bool i, bool b){
	if(i and not b) cout << MGray;
	else if(not b) cout << LGray;
	else if(i) cout << LGray;
	else cout << MGray;
}

void printr(const d_elem &d, int i, bool b){
	cout << d.first;
	space(i - d.first.size()
			- d.second.first.size());
	cout << d.second.first;
	
	if(not b) cout << "   ";
	else cout << endl;
}

#endif