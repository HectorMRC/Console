#ifndef DICTIONARY_HH
#define DICTIONARY_HH

#include "Types.hh"

class Dictionary{
private:
	//BASES DE DADES:
	dictionary dict; //Diccionari principal
	references refr; //Referencies al diccionari principal

	equivalent equv; //Equivalencies a dict/refr
	//definition atom; //especificacions de la paraula

	//FUNCIONS AUXILIARS:
	bool nEqual(const char &c,
				const char &ctrl){
	/*pre: */
	/*post: */

		return c != ctrl;
	}

	bool nDictEnd(const dic_ptr &it){
	/*pre: cert*/
	/*post: indica si it apunta al final del dict o no.*/

		return it != dict.end();
	}

	bool nRefrEnd(const ref_ptr &it){
	/*pre: cert*/
	/*post: indica si it apunta al final del banc de
	referencies o no.*/

		return it != refr.end();
	}

	bool nEquvEnd(const equ_ptr &it){
	/*pre: cert*/
	/*post: indica si it apunta al final del banc
	d'equivalencies o no.*/

		return it != equv.end();
	}

	str wordRef(const ref_ptr &it){
	/*pre: it apunta a una direcció valida del banc
	de referencies*/
	/*post: retorna el contingut Word del element al que fa
	referencia el punter it.*/

		return (*it).second->first;
	}

	str infoRef(const ref_ptr &it){
	/*pre: it apunta a una direcció valida del banc
	de referencies*/
	/*post: retorna el contingut Info del element al que fa
	referencia el punter it*/

		return (*((*it).second)).second.second;
	}

	dic_ptr isIn(const str &w,
				 const str &t){
	/*pre: cert*/
	/*post: en cas de que la paraula w i la traducció t,
	com a conjunt, existeixin al diccionari: retorna un
	punter a la posició on es troben; altrament retorna un
	punter a dict.end*/

		dic_ptr it = dict.find(w);
		for(; nDictEnd(it) and it->first == w; it++)
			if((*it).second.first == t) return it;

		return dict.end();
	}

	equ_ptr isInEqu(const str &w,
				 	const str &t,
				 	bool b){
	/*pre: cert*/
	/*post: en cas de que l'equivalencia w->t existeixi al
	banc d'equivalencies: retorna el punter a dita equiva-
	lencia; altrament retorna un punter a equv.end*/

		equ_ptr it = equv.find(w);
		if(not nEquvEnd(it) or 
		  ((not b and (equv[w].first)->first != t) or
		  (b and (equv[w].second)->first != t)))
			return equv.end();

		else return it;
	}

	ref_ptr findRefOf(const str &t,
					  const dic_ptr &p){
	/*pre: cert*/
	/*post: retorna un punter a la referencia de t a p;
	en cas de no existir retorna un punter nul*/
		
		ref_ptr it = refr.find(t);
		for(; nRefrEnd(it) and it->first == t; it++)
			if(it->second == p) return it;

		return refr.end();
	}

	v_d_elem getEquData(const str &s){
	/*pre: cert*/
	/*post: retorna un vector de longitud màxima 2, on,
	per cada posició: el primer element és el mot al qual
	equival l'argument s, el segon la traducció d'aquest i
	el tercer la informació. En cas de no exisitir l'equi-
	valencia s es retorna un vector buit.*/

		v_d_elem v;
		if(nEquvEnd(equv.find(s))){
			if(nDictEnd(equv[s].first))
				v.push_back(*(equv[s].first));
			else v.push_back({nullstr,{nullstr, nullstr}});

			if(nRefrEnd(equv[s].second)){
				dic_ptr it = (equv[s].second)->second;
				data aux = {it->first,(it->second).second};
				v.push_back({(it->second).first, aux});
			}
		}

		return v;
	}

	v_d_elem getDicData(const str &s){
	/*pre: cert*/
	/*post: retorna un vector amb les dades de totes les
	instancies del mot s que es trobin al diccionari. Si
	no existeix cap instancia el vector retornat es buit*/

		v_d_elem v;
		dic_ptr it = dict.find(s);
		for(; nDictEnd(it) and it->first == s; it++)
			v.push_back({s, it->second});

		return v;
	}

	v_d_elem getRefData(const str &s){
	/*pre: cert*/
	/*post: retorna un vector amb les dades de totes les
	instancies del mot s que es trobin al banc de
	referencies. Si no existeix cap instancia el vector
	retornat es buit*/

		v_d_elem v;
		ref_ptr it = refr.find(s);
		for(; nRefrEnd(it) and it->first == s; it++)
			v.push_back({s, {wordRef(it), infoRef(it)}});

		return v;
	}

	void align(const v_str &v, const str &s, int &i, bool *b){
	/*pre:  cert*/
	/*post: incrementa o decrementa la posició marcada per i
	per tal d'obtenir una major precisió*/

		if(i >= (int)v.size()) i = v.size()-1;
		else if(s[0] < v[i][0]){
			if(not b) b = new bool(false);
			if(not *b) align(v, s, --i, b);
		}
		else if(s[0] > v[i][0]){
			if(not b) b = new bool(true);
			if(*b) align(v, s, ++i, b);
		}
	}

	v_d_elem wordSegment(const str &s){
	/*pre: cert*/
	/*post: retorna un vector amb les dades de totes les
	instancies al diccionari que comencen pel segment s.
	Si no existeix cap instancia amb aquesta propietat el
	vector retornat es buit*/

		if(not dict.size()) return v_d_elem();
		//Copiem totes les Words sense repeticions:
		v_str v(dict.size());
		int i = 0;
		for(dic_ptr it = dict.begin(); nDictEnd(it); it++)
			if(not search<str>(it->first, 0, i, v, nullptr))
				v[i++] = it->first;
		//Busquem la posició del mot que més s'assembli a s
		if(not search<str>(s, 0, i, v, &i))
			align(v, s, i, nullptr);
		/*A partir del mot trobat, inserim al vector tots
		aquell que compleixen la similitud*/ 
		v_d_elem segment;
		dic_ptr it = dict.find(v[i]);
		for(; nDictEnd(it) and (it->first).substr(0, s.size()) ==
								s; it = dict.find(v[++i]))
			segment.push_back(*it);

		return segment;
	}

	v_d_elem tranSegment(const str &s){
	/*pre: cert*/
	/*post: retorna un vector amb les dades de totes les
	instancies al banc de referencies que comencen pel
	segment s. Si no existeix cap instancia amb aquesta
	propietat el vector retornat es buit*/

		if(not refr.size()) return v_d_elem();
		//Copiem totes les Words sense repeticions:
		v_str v(refr.size());
		int i = 0;
		for(ref_ptr it = refr.begin(); nRefrEnd(it); it++)
			if(not search<str>(it->first, 0, i, v, nullptr))
				v[i++] = it->first;
		//Busquem la posició del mot que més s'assembli a s
		if(not search<str>(s, 0, i, v, &i))
			align(v, s, i, nullptr);
		/*A partir del mot trobat, inserim al vector tots
		aquell que compleixen la similitud*/ 
		v_d_elem segment;
		ref_ptr it = refr.find(v[i]);
		for(; nRefrEnd(it) and (it->first).substr(0, s.size()) ==
								s; it = refr.find(v[++i]))
			segment.push_back({it->first,{(it->second)->first,
										  ((it->second)->second).second}});

		return segment;
	}

	v_d_elem getAllDic(){
	/*pre: cert*/
	/*post: retorna un vector amb totes les dades del
	diccionari: word/tran/info*/

		v_d_elem v(dict.size());
		dic_ptr it = dict.begin();
		for(int i = 0; nDictEnd(it); it++, i++)
			v[i] = *it;

		return v;
	}


	v_d_elem getAllRef(){
	/*pre: cert*/
	/*post: retorna un vector amb totes les dades de
	les referencies: word/tran/info*/

		v_d_elem v(refr.size());
		ref_ptr it = refr.begin();
		for(int i = 0; nRefrEnd(it); it++, i++)
			v[i] = {it->first, {wordRef(it), infoRef(it)}};
		
		return v;
	}

	str getAtom(const str &w, const str &t){ //ACTUALMENT FORA D'US
	/*pre: cert*/
	/*post: retorna un pair amb les especificacions de
	la paraula/definició a la que apunta it. En cas de
	apuntar enlloc retorna un def buit.*/
		
		if(not nDictEnd(isIn(w, t))) return nullstr;
		return nullstr; //atom[w + '.' + t];
	}

	str normalize(const d_elem &elem,
				  const char &ctrl){
	/*pre: cert*/
	/*post: normalitza el contingut del d_elem en el
	format de lectura adient per poder imprimir-lo
	en un fitxer inteligible en proximes lectures.*/

		return 	elem.first + ctrl +
				elem.second.first + ctrl +
				elem.second.second + ctrl;
	}

	str normalize(const equ_ptr it,
				  const char &ctrl,
				  const char &link,
				  bool b){
	/*pre: cert*/
	/*post: normalitza el contingut de it en el
	format de lectura adient per poder imprimir-lo
	en un fitxer inteligible en proximes lectures.*/

		str norma = it->first + link;
		if(not b) norma += ((it->second).first)->first;
		else norma += ((it->second).second)->first;
		norma += ctrl; norma += b + '0'; norma += ctrl;
		return norma;
	}

	str getStr(const str &s,
			   const str &a,
			   bool *b){
	/*pre: cert*/
	/*post: retorna el text segmentat, des del inici, fins
	a la primera instancia del caracter ctrl.*/

		if(b) *b = nEqual(s[s.find_first_of(a)],a[0]);
		return s.substr(0, s.find_first_of(a));
	}

	void cutStr(str &s,
				const str &a){
	/*pre: cert*/
	/*post: retorna el text segmentat, des de la primera
	instancia del caracter ctrl +1, fins al final del
	string*/

		s = s.substr(s.find_first_of(a)+1);
	}

	//FUNCIONS PRIORITARIES:
	bool inDict(const str &w,
				const str &t,
				const str &i
				/*const str &e*/){
	/*pre: cert*/
	/*post: insereix un nou element al diccionari. En cas
	de fer-ho sense incidents retorna true; altrament
	retorna false*/

		if(nDictEnd(isIn(w, t))) return false; //exist
		dict.insert(d_elem(w, data(t, i))); //inserció w-ti
		refr.insert(r_elem(t, isIn(w, t))); //creació t->w
		//atom[w + '.' + t] = e; //registre de les especific.
 		//Validació:
		return exist(w, t, nullptr);
	}

	bool inEquv(const str &w,
				const str &t,
				const str &i){
	/*pre: cert*/
	/*post: insereix un nou element al banc d'equivalencies.
	En cas de fer-ho sense incidents retorna true; altrament
	retorna false*/

		if(not nEquvEnd(equv.find(w)))
			equv[w] = {dict.end(), refr.end()};

		if(nEqual(i[0],'1')) equv[w].first = dict.find(t);
		else equv[w].second = refr.find(t);

		bool b{i[0] == '1'};
		return exist(w, t, &b);
	}

	bool rmDict(const str &w,
				const str &t){
	/*pre: cert*/
	/*post: elimina un element del diccionari. En cas de
	fer-ho sense incidents retorna true; altrament
	retorna false*/

		if(not nDictEnd(isIn(w, t))) return false; //no w-ti
		refr.erase(findRefOf(t, isIn(w, t))); //elim. t->w
		dict.erase(isIn(w, t)); //elim. la definició w-ti
		//Validació:
		return not exist(w, t, nullptr);
	}

	bool rmEquv(const str &w,
				const str &t){
	/*pre: cert*/
	/*post: elimina un element del banc d'equivalencies.
	En cas de fer-ho sense incidents retorna true;
	altrament retorna false*/

		if(not nEquvEnd(equv.find(w))) return false;
		if(t[0] == '0') equv[w].first = dict.end();
		else equv[w].second = refr.end();

		if(equv[w] == pair<dic_ptr, ref_ptr>(dict.end(), refr.end()))
			equv.erase(w);
		//Validació:
		return true;
	}

public:
	//CONSTRUCTORA:
	Dictionary(){}

	//DESTRUCTORA:
	~Dictionary(){}

	//MODIFICADORS:
	bool load(const str &s,
			  const char &ctrl,
			  const char &link){
	/*pre: cert*/
	/*post: llegeix el fitxer s i en transfereix les dades
	als corresponents components del dicionari. En
	cas de fer-ho sense incidents retorna true;
	altrament retorna false.*/

		/*Pas del contingut sencer del fitxer d'entrada s
		a un diposit string*/
		str sgm{nullstr};
		if (FILE *fp = fopen(s.c_str(), "r")){
			char buf[1024];
			while (size_t len = fread(buf, 1, sizeof(buf), fp))
				sgm.insert(sgm.end(), buf, buf + len);
			fclose(fp);
		}
		else return false;

		/*Lectura i registre de les dades del fitxer
		segons el format d'escriptura/lectura
		pertinent al diccionari*/
		str symb{ctrl, link};
		while(sgm.size() > 1){
			bool neword{false};
			str word {getStr(sgm, symb, &neword)};
			cutStr(sgm, symb);

			str tran {getStr(sgm, symb, nullptr)};
			cutStr(sgm, symb);

			str info {getStr(sgm, symb, nullptr)};
			cutStr(sgm, symb);

			//str spec {getStr(sgm, symb, nullptr)};
			//cutStr(sgm, symb);

			/*Agregació del contingut al diccionari i al
			banc de referencies*/
			if((neword and not input(word, tran, info, false)) or
			   (not neword and not input(word, tran, info, true)))
				return false;
		}
		
		//Validació:
		return true;
	}

	bool save(const str &s,
			  const char &ctrl,
			  const char &link){
	/*pre: cert*/
	/*post: guarda els elements registrats al diccionari
	al fitxer s, respectant el format de lectura.
	En cas de fer-ho sense incidents retorna true;
	altrament retorna false.*/

		ofstream outfile(s.c_str()); //obertura del fitxer
		if(outfile.fail()) return false;

		/*Vectorització i registre del contingut resultant
		en el format corresponent d'escriptura/lectura*/
		v_d_elem v = getAllDic();
		for(int i = 0; i < (int)v.size(); i++)
			outfile << normalize(v[i], ctrl);

		/*Registre de les equivalencies existents en el
		format corresponent d'escriptura/lectura*/
		for(equ_ptr it = equv.begin(); it != equv.end(); it++){
			if(nDictEnd((it->second).first))
				outfile << normalize(it, ctrl, link, false);
			if(nRefrEnd((it->second).second))
				outfile << normalize(it, ctrl, link, true);
		}
		
		outfile.close();

		//Validació:
		return true;
	}

	bool input(const str &w,
			   const str &t,
			   const str &i,
			   /*const str &e,*/
			   bool neword){
	/*pre: cert*/
	/*post: insereix un nou element al dict o al equv
	segons neword indiqui. En cas de fer-ho sense
	incidents retorna true; altrament retorna false*/

		if(neword) return inDict(w, t, i);
		else return inEquv(w, t, i);
	}

	bool remove(const str &w,
				const str &t,
				bool d_word){
	/*pre: cert*/
	/*post: elimina un element del dict o equv segons
	d_word indiqui. En cas de fer-ho sense incidents
	retorna true; altrament retorna false*/
		
		if(d_word) return rmDict(w, t);
		else return rmEquv(w, t);
	}

	bool edit(const str &w,		//paraula (key)
			  const str &t, 	//traducció de referencia
			  const str &x,		//nova paraula
			  const str &u,  	//nova traducció
			  const str &i 	//nova informació
			  /*const str &e*/){ 	//noves especificacions
	/*pre: cert*/
	/*post: edita la paraula w del diccionari. En cas de
	fer-ho sense incidents retorna true; altrament
	retorna false*/

		if(not nDictEnd(isIn(w, t))) return false; //no w-ti
		if(w != x) //si s'ha modificat la paraula w:
			return remove(w, t, true) and input(x, u, i, /*e,*/ true);
		//Altrament, si la informació i s'ha modificat:
		if((*isIn(w, t)).second.second != i)
			(*isIn(w, t)).second.second = i;
		//i/o si la traducció t s'ha modificat:
		if(t != u){
			refr.erase(findRefOf(t, isIn(w, t)));
			(*isIn(w, t)).second.first = u;
			refr.insert(r_elem(u, isIn(w, u)));
		}
		//if(not nDictEnd(isIn(w,t))) atom[w + '.' + t].erase();
		//if(getAtom(w, t) != e) atom[x + '.' + u] = e;
		
		//Validació:
		return exist(x, u, nullptr);
	}

	//CONSULTORS:
	bool whereExist(const str &s,
					bool b){
	/*pre: cert*/
	/*post: retorna true si i només si b = false i s es
	troba al diccionari, o bé es troba al banc de refr i
	b = true; altrament retorna false*/

		return
		(b and  nRefrEnd(refr.find(s))) or
		(not b and nDictEnd(dict.find(s)));
	}

	bool exist(const str &w, const str &t, bool *b){
	/*pre: cert*/
	/*post: indica si una definició existeix al diccionari;
	altrament retorna false.*/
		if(not b) return nDictEnd(isIn(w, t));
		else return nEquvEnd(isInEqu(w, t, *b));
	}

	bool clear(){
	/*pre: cert*/
	/*post: Esborra el contingut de tots els maps del
	diccionari. En cas de fer-ho sense incidents retorna
	true; altrament retorna false.*/

		dict.clear();
		refr.clear();
		equv.clear();
		
		return dict.empty() and
			   refr.empty() and
			   equv.empty();		
	}

	str getInfo(const str &w, const str &t/*, bool b*/){
	/*pre: cert*/
	/*post: retorna la informació de la definició w-t
	registrada al diccionari; o bé les especificacions,
	segons b indiqui. Si la definició no existeix
	returna un str buit.*/

		if(not exist(w, t, nullptr)) return nullstr;
		
		//if(b) return getAtom(w, t);
		return (*isIn(w, t)).second.second;
	}

	v_d_elem getData(const str &s,
					 bool *b){
	/*pre: cert*/
	/*post: retorna un vector ordenat amb les dades de totes
	les instancies de la paraula s al dict o a refr segons
	indiqui el booleà b. En cas de que s no exiteixi el
	vector és buit*/

		if(not b) return getEquData(s);
		if(*b) return getRefData(s);
		return getDicData(s);
	}

	v_d_elem getSegment(const str &s,
						bool b){
	/*pre: cert*/
	/*post: retorna un vector ordenat amb les dades de totes
	les instancies que comencen pel segment s al diccionari o
	al banc de referencies segons indiqui b. En cas de no
	existir cap coincidencia el vector a retornar es null.*/

		if(b) return tranSegment(s);
		else return wordSegment(s);
	}

	v_d_elem getAll(bool b){
	/*pre: cert*/
	/*post: retorna un vector amb tots els elements del
	diccionar o del banc de referencies*/

		if(b) return getAllRef();
		return getAllDic();
	}
};

#endif