#include "React.hh"

int main()
{
	Dictionary registre; //Diccionari 
	str fname{defDict}; //nom d'arxiu obert
	data langs(flang,slang);
	bool save{true}; //controlador d'estat

	cslInfo();
	
	v_str cmd; //Vector de comandes
	while(RAR(cmd, fname)){ //Read and Run
		if(not isCommand(cmd[0])) Word(cmd, registre, langs);
		else if(isCl(cmd[0])) Close(cmd, fname, langs, registre, save);
		else if(isEq(cmd[0])) Input(cmd, registre, save, false);
		else if(isIn(cmd[0])) Input(cmd, registre, save, true);
		else if(isLd(cmd[0])) Load(cmd, fname, langs, registre, save);
		else if(isLs(cmd[0])) LetsSee(cmd, fname, langs, registre);
		else if(isMd(cmd[0])) Modify(cmd, langs, registre, save);
		else if(isNp(cmd[0])) NewPage(cmd, registre);
		else if(isRm(cmd[0])) Remove(cmd, registre, save);
		else if(isSv(cmd[0])) Save(cmd, fname, langs, registre, save);
		else if(isTr(cmd[0])) Translate(cmd, langs, registre);

		else if(isEnd(cmd[0]) and End(cmd, save)) break;

		cmd.clear();
	}

	Cancel(cmd);
}