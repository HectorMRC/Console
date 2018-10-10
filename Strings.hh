#ifndef STRINGS_HH
#define STRINGS_HH

static const vector<str> tag{
	"\e[1;32m[i]\e[0m ", "\e[1;33m[!]\e[0m ",
	//        0                    1
	"\e[1;33m[?]\e[0m ", "\e[1;31m[ERROR]\e[0m " ,
	//        2                      3
	"\e[1;34m[>]\e[0m "
};	//        4

static const str usr{"\e[1;34mUserCommand:\e[0m "};
static const str defDict{"Dictionary"};
static const str flang{"first"};
static const str slang{"second"};

static const str I0{"Diccionari de paraules."};
static const str I1{"Consola versió 5.1.0"};

static const str C0{"as"};
static const str C1{".."};
static const str C2{"to"};
static const str C3{"from"};

static const str U0{"::"};
static const str U1{"["};
static const str U2{"] "};
static const str U3{" | "};
static const str U4{":"};
static const str U5{", "};
static const str U6{" o potser: "};

static const str E0{": La quantitat d'arguments no correspon: "};
static const str E1{": Ja ha estat registrada anteriorment com:"};
static const str E2{": La paraula definida no existeix."};
static const str E3{": No s'ha pogut obrir el fitxer."};
static const str E4{": S'ha produit un error durant l'eliminació."};
static const str E5{": No s'ha definit cap fitxer d'entrada/sortida."};
static const str E6{": S'ha produit un error durant l'escriptura."};
static const str E7{": No s'ha trobat la comanda."};
static const str E8{": No s'ha trobat la paraula."};
static const str E9{": S'ha produit un error durant el registre."};
static const str E10{": S'ha produit un error durant l'edició."};
static const str E11{": Cal definir l'argument d'assignació: " + C0 + "."};
static const str E12{": No s'ha assignat cap valor despres de l'argument: " + C0 + "."};
static const str E13{": El conjunt paraula/traducció definit no existeix."};
static const str E14{": El nom del fitxer d'entrada/sortida no segueix el format adient."};
static const str E15{": No s'ha pogut buidar el contingut del diccionari."};
static const str E16{": El diccionari ha sigut alterat des de l'últim salvament."};
static const str E17{": Cal definir algún argument de direcció: " + C2 + " o " + C3 + "."};
static const str E18{": No s'ha assignat cap valor despres de l'argument: " + C2 + "o" + C3 + "."};

static const str N0{"Manquen "};
static const str N1{"Sobren "};
static const str N2{" argument/s."};

static const str W0{": La lectura s'ha completat sense incidents."};
static const str W1{": La paraula s'eliminarà de manera definitiva."};
static const str W2{": L'eliminació s'ha completat sense incidents."};
static const str W3{": El registre s'ha guardat sense incidents."};
static const str W4{": El registre s'ha efectuat amb èxit."};
static const str W5{": No s'han guardat els canvis pertinents."};
static const str W6{": L'edició s'ha completat sense incidents."};
static const str W7{": Aquesta acció modificarà el contingut del diccionari."};
static const str W8{": El nom del fitxer ha de respectar l'estructura: lang1.lang2.dat"};
static const str W9{": Aquesta acció formatarà el contingut actual del diccionari."};
static const str W10{" Aquesta acció reestablirà l'estat anteriorment guardat del diccionari."};
static const str W11{": Qualsevol canvi sense guardar es perdrà irreversiblement."};
static const str W12{": El reinici del diccionari s'ha efectuat adequadament."};
static const str W13{": S'ha procedit a finalitzar el diccionari."};
static const str W14{": Tots els canvis han sigut salvats amb antelació."};
static const str W15{": La equivalencia s'ha efectuar sense incidents."};
static const str W16{"Potser volies dir: "};

static const str Q0{"Vols continuar? (S/n): "};
static const str Q1{"Vols registrar-la? (S/n): "};
static const str Q2{"Vols guardar-los ara? (S/n): "};

static const str A0{"S"};
static const str A1{" equival a "};

static const str T0{"Fitxer: "};
static const str T2{"D'interès: "};
static const str T3{"Especific: "};

static const str S0{"[Fitxer] "};
static const str S1{"[D'interès] "};
static const str S2{"[Especific] "};

#endif