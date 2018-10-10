#ifndef SYMBOLS_HH
#define SYMBOLS_HH

//Signes de comanda:
static const vector<str> command{
	"cc","cl","end","eq","in","ld","ls","md","np","rm","sv","tr"
}; //0    1     2    3    4    5    6    7    8    9    10   11
//cancel|close|end||input|load|see|edit|new|remove|save|translate
//Signes:
static const char ctrl = '#'; //control
static const char link = '@'; //equival
static const char asig = '/'; //assigna

/*La cerca ara es troba al fitxer: Types.hh*/

//Funcions de simbologia:
bool isCommand(const str &s){
	return search<str>(s, 0, command.size()-1, command, nullptr);
}

bool isCC(const str &s){
	return s == command[0];
}

bool isCl(const str &s){
	return s == command[1];
}

bool isEnd(const str &s){
	return s == command[2];
}

bool isEq(const str &s){
	return s == command[3];
}

bool isIn(const str &s){
	return s == command[4];
}

bool isLd(const str &s){
	return s == command[5];
}

bool isLs(const str &s){
	return s == command[6];
}

bool isMd(const str &s){
	return s == command[7];
}

bool isNp(const str &s){
	return s == command[8];
}

bool isRm(const str &s){
	return s == command[9];
}

bool isSv(const str &s){
	return s == command[10];
}

bool isTr(const str &s){
	return s == command[11];
}

bool finalize(const str &s){
	return isCC(s);
}

#endif