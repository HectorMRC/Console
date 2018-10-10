#ifndef REACT_HH
#define REACT_HH

#include "Dictionary.hh"
#include "Symbols.hh"
#include "Strings.hh"
#include "Colors.hh"
#include "StrUtils.hh"
#include "AlgUtils.hh"

void Cancel(const v_str &v){
	cout << tag[0] << v[0] << W13 << endl;
}

bool End(const v_str &v, bool &save){
	if(not argCtrl(v, 1)) return false;

	return (Warning(save, v[0], W14, E16)
			or Ask(v[0],W11));
}

void Close(const v_str &v,
		   str &fname,
		   data &lang,
		   Dictionary &d,
		   bool &save){

	if(not argCtrl(v, 1)) return;

	if(End(v, save) and
	   Warning(d.clear(), v[0], W12, E15)){
		lang = {flang,slang};
		fname = defDict;
		save = true;
	}
}

void Input(const v_str &v,
		   Dictionary &d,
		   bool &save,
		   bool to){ //input to dict?

	if(v.size() < 4) return (void)argCtrl(v, 4);

	bool from{false};
	str w{nullstr}, t{nullstr}, i{nullstr};
	if((to and not getIt(v, w, t, nullptr)) or 
	   (not to and not getIt(v, w, t, &from)))
		return;
	
	if(to) RAF(i, LBlue + T2 + Default);
	else if(from) i = "1"; else i = "0";

	if((to and Warning(d.input(w, t, i, true), v[0], W4, E9)) or
	   (not to and Warning(d.input(w, t, i, false), v[0], W15, E9)))
		save = false;
}

void Load(const v_str &v,
		  str &fname,
		  data &lang,
		  Dictionary &d,
		  bool &save){

	if(v.size() > 2) return (void)argCtrl(v, 2);

	str tName{fname};
	if(v.size() == 2) tName = v[1];
	if(FileErr(v[0], tName)) return;
	
	if((not save) and 
	   ((v.size()%2 and not Ask(v[0],W9+W11)) or 
		(not v.size()%2 and
		 not Ask(v[0],W10+W11))))
		return;

	if(not d.clear()) return;
	if(Warning(d.load(tName,ctrl,link),v[0],W0,E3)){
		getName(tName, lang);
		fname = tName;
		save = true;
	}
}

void LetsSee(const v_str &v,
			 const str &fname,
			 const data &langs,
			 Dictionary &d){

	if(not argCtrl(v, 1)) return;

	v_d_elem vDic{d.getAll(false)};
	v_d_elem vRef{d.getAll(true)};

	int vDicSize{antropy(vDic)};
	int vRefSize{antropy(vRef)};

	cout << Magenta << U1 << langs.first;
	cout << U3 << vDicSize << U2;
	space(27-langs.first.size()-isize(vRef.size()));
	cout << U1 << langs.second << U3;
	cout << vRefSize << U2 << endl;

	print(vDic, vRef);

	cout << Magenta << U1 << fname << U3;
	cout << vDic.size() << U4;
	cout << indx(vDicSize, vRefSize) << U2;
	cout << endl;
}

void Modify(const v_str &v,
			data &l,
			Dictionary &d,
			bool &s){
	if(v.size() < 4) return (void)argCtrl(v, 4);

	str w{nullstr}, t{nullstr};
	if(not getIt(v, w, t, nullptr) or
	   not existCtrl(v[0], w, t, d)) return;

	str nW{nullstr}, nT{nullstr}, nI{nullstr};
	RAT(nW, nT, nI, l);

	if(isC1(nW)) nW = w;
	if(isC1(nT)) nT = t;
	if(isC1(nI.substr(0,nI.find_first_of(" \n")))){
		str s = nI.substr(nI.find_first_of(" \n"));
		nI = d.getInfo(w, t).substr(0,
				d.getInfo(w, t).find_last_of("\n"));
		nI += s;
	}

	if(not Ask(v[0], W7)) return;
	if(Warning(d.edit(w,t,nW,nT,nI),v[0],W6,E10))
		s = false;
}

void NewPage(const v_str &v, Dictionary &d){
	if(not argCtrl(v, 1)) return;
	system("clear");
}

void Remove(const v_str &v, Dictionary &d, bool &s){
	if(v.size() < 4) return (void)argCtrl(v, 4);

	str w{nullstr}, t{nullstr};
	if(not getIt(v, w, t, nullptr)) return;
	if(Warning(d.remove(w, t, true), v[0], W2, E4))
		s = false;
}

void Save(const v_str &v,
		  str &fname,
		  data &lang,
		  Dictionary &d,
		  bool &save){

	if(v.size() > 2) return (void)argCtrl(v, 2);
	
	str tName{fname};
	if(v.size() == 2) tName = v[1];
	if(FileErr(v[0], tName)) return;

	if(Warning(d.save(tName,ctrl,link),v[0],W3,E6)){
		getName(tName, lang);
		fname = tName;
		save = true;
	}
}

void Translate(const v_str &v,
			   data &langs,
			   Dictionary &d){

	if(v.size() < 3) return (void)argCtrl(v, 3);
	if(not isC2C3(v[1]))
		return (void)C2C3Err(v[0], false);

	str r{nullstr}, t{nullstr};
	trnl(v,r,t,d,isC3(v[1]));

	WordLang(r, langs, isC3(v[1]));
	WordLang(t, langs, isC2(v[1]));
	cout << endl;
}

void Help(const v_str &v, Dictionary &d){
	if(not argCtrl(v, 1)) return;
}

void Word(const v_str &v, Dictionary &d, data &l){
	str w{nullstr};
	fusion(v, w, 0, v.size());

	bool b{false};
	bool exist = WordData(w, d, l, &b);
	if(exist) cout << endl;
	b = not b;
	if(not WordData(w, d, l, &b) and not exist){
		if(not WordData(w, d, l, nullptr)){
			cout << tag[1] << w << E2 << endl;
			if(segments(w, d)) cout << endl;
		}
	}
}

#endif