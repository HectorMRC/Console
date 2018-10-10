#ifndef ALGUTILS_HH
#define ALGUTILS_HH

bool argCtrl(const v_str &v, int argc){
/*Controla que el nombre d'arguments sigui el
correcte*/
	int dif{argc - (int)v.size()};
	if(not dif) return true;
	
	cout << tag[3] << v[0] << E0;
	if(dif > 0) cout << N0 << dif;
	else cout << N1 << dif * -1;
	cout << N2 << endl;

	return false;
}

bool existCtrl(const str &c,
			   const str &w,
			   const str &t,
			   Dictionary &d){
/*Controla que la definició proposada existeixi
al diccionari o al banc de registres segons b*/
	if(d.exist(w,t,nullptr)) return true;
	cout << tag[3] << c << E13 << endl;
	return false;
}

bool findC0(const v_str &v){
	for(str s: v) if(isC0(s)) return true;
	return false;
}

void parse(const str s, v_str &v){
/*Vectoritza un str no null*/

	if(s.size() != 0){
		if(s.substr(0, s.find_first_of(' ')) != nullstr)
			v.push_back(s.substr(0,s.find_first_of(' ')));
		if(s.find_first_of(' ') != s.npos)
			parse(s.substr(s.find_first_of(' ')+1), v);
	}
}

int isize(int i){
	if(i) return 1 + isize(i/10);
	else return 0;
}

bool RAR(v_str &cmd, const str &fname){
/*Read and Run*/
	
	str cmdLine{nullstr};
	while(not cmdLine.size()){
		RARInfo(fname);
		getline(cin, cmdLine);
	}

	parse(cmdLine, cmd);
	return not finalize(cmd[0]);
}

void RAF(str &s, const str &name){
/*Read and Formatize*/

	str newline{nullstr};
	for(int i = 0;; i++){
		RAFInfo(name, i);
		getline(cin, newline);

		if(isEnd(newline)) break;
		s += newline+"\n";
	}
}

void RAT(str &w, str &t, str &i, data &l){
/*Read and Transfer*/

	RATInfo(l, false);
	while(not w.size())
		getline(cin, w);

	RATInfo(l, true);
	while(not t.size())
		getline(cin, t);

	RAF(i, LBlue + T2 + Default);
}

void getName(const str &s, data &l){
	l.first = s.substr(0, s.find_first_of("."));
	str t = s.substr(s.find_first_of(".")+1);
	l.second = t.substr(0, t.find_first_of("."));
}

bool okName(const str &s){
	return s.find_first_of(".") != s.find_last_of(".");
}

bool FileErr(const str &c, const str &f){
	if(not isDefDict(f) and okName(f)) return false;
	
	cout << tag[3] << c;
	if(isDefDict(f)) cout << E5 << endl;
	else{
		cout << E14 << endl << tag[1];
		cout << f << W8 << endl;
	}

	return true;
}

/*void Spec(const str &w, const str &t, Dictionary &d, bool b){
	cout << Magenta;
	if(b) cout << d.getInfo(t, w, true);
	else cout << d.getInfo(w, t, true);
	cout << Default << endl;
}
*/

bool WordData(const str &s,
			  Dictionary &d,
			  data &l, 
			  bool *b){
/*Imprimeix les dades de la paraula s*/
	v_d_elem velem{(d.getData(s, b))};

	if(not velem.size()) return false;
	for(uint nl{0}, i{0}; i < velem.size(); i++){
		if(velem[i].first != nullstr){
			if(nl) cout << endl;
			if(b) WordLang(s, l, *b); //si apunta
			else WordLang(s + LYellow + A1 + Default +
						  velem[i].first, l, i == 1);
			
			if(not b) b = new bool(i == 1);
			WordLang(velem[i].second.first, l, not *b);
			cout << LMagenta << S1 << Default;
			cout << velem[i].second.second << endl;
			nl = true;
		}
	}

	return true;
}

void segPrint(v_d_elem &v){
	for(uint i = 0; i < v.size(); i++){
		cout << v[i].first;
		if(i < v.size()-1) cout << U5;
	}
}

bool segments(const str &w,
			  Dictionary &d){
/*Imprimeix els segments trobats*/
	v_d_elem first{d.getSegment(w, false)};
	v_d_elem second{d.getSegment(w, true)};
	if(first.size() or second.size()){
		cout << tag[2] << Yellow << W16;
		cout << Default;
		segPrint(first);
		if(first.size() and second.size())
			cout << Yellow << U6 << Default;
		segPrint(second);
	}

	return first.size() or second.size();
}

bool getIt(const v_str &v, str &w, str &t, bool *b){
	uint i = 2;
	for(w = v[1]; (not b and not isC0(v[i])) or 
				  (b and not isC2C3(v[i])); i++)
		if(i < v.size()) w += ' ' + v[i];
		else return C0Err(v[0], false);

	if(b) *b = isC3(v[i]);
	if(++i == v.size()) return (b? C2C3Err(v[0], true): C0Err(v[0], true));
	for(t = v[i], i++; i < v.size(); i++)
		t += ' ' + v[i];

	return true;
}

int antropy(const v_d_elem &v){
/*Indica quants elements hi ha diferents*/

	set<string> conj;
	for(uint i = 0; i < v.size(); i++)
		conj.insert(v[i].first);

	return conj.size();
}

double indx(const double &x, const double &y){
/*Index diferencial entre l'idioma A i el B*/
	return ((x/y)>1? y/x : x/y);
}

void fusion(const v_str &v, str &w, uint i, uint n){
	for(w = v[i++]; i < n; w += ' ' + v[i], i++);
}


void print(const v_d_elem &vDic,
		   const v_d_elem &vRef){

	for(uint i = 0; i < vDic.size(); i++){
		colorize(i%2, false);
		printr(vDic[i], 30, false);
		
		colorize(i%2, true);
		printr(vRef[i], 30, true);
	}
}

void trnl(const v_str &v,
		  str &r,
		  str &t,
		  Dictionary &d,
		  bool b){

	t = nullstr;
	for(uint i = 2, n = v.size(); i < v.size();){
		str aux{nullstr};
		str color{Default};

		bool auxb{b};
		fusion(v, aux, i, n);
		v_d_elem velem{(d.getData(aux, &auxb))};
		if(velem.size()){
			if(velem.size() > 1) color = Green;
			t += color + velem[0].second.first + ' ';
			r += color + aux + ' ';
			i = n; n = v.size();
		}
		else{
			if(n == i+1){
				t += Red + v[i] + ' ';
				r += Red + v[i] + ' ';
				n = (++i)+1;
			} 
			else n--;
		}
	}
}

#endif