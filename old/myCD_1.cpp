#include <iostream>
#include <windows.h>
#include <sys/stat.h> // if (stat(path
using namespace std;

// moje_CD

//string cesta;

bool existuje_adresar(const char* path) {
struct stat info;
if (stat(path, &info) != 0){
return false;
}
return (info.st_mode & S_IFDIR) != 0;
}

int main(int argc, char **argv) {

if ( argc == 1 ){
cerr<<"myCD adresar\n";
return 1;
}

// tyhle dva radky jsou zasadni a bez nich to nejde
// nastavime globalni locale podle systemu (klicové pro spravnou konverzi a diakritiku)
locale::global(locale("")); // bez tototo i FUNGUJE al eradeji ponechat
// nastaveni C knihoven na systemove locale, aby fungovalo mbstowcs/wcstombs
setlocale(LC_ALL, ""); // bez tohoto NEfunguje
    
string cesta = argv[1];
cout<<"CD "<<'"'<<cesta<<'"'<<endl;

if (-not(existuje_adresar(cesta.c_str()))) {
cerr<<"neexistuje adresáø: "<<cesta<<"\n";
return 1;
}

SetCurrentDirectoryA(cesta.c_str());
cerr<<"byl spusten novy process cmd.exe. pro ukonceni napis exit<Enter>\n";	
system("cmd.exe");
/* 
spusti se nova instance "cmd.exe" a vtom pripade je tento "myCD_1.exe" jako rodic
a potomek cili, vnem spusteny "cmd.exe" zdedi jeho vlasnost, takze i PWD
ale paklize se napise exit a opusti se tim nove spustena instance "cmd.exe"
adresar je opet stejny jako byl puvodne"
 tzn. je to stejne jako na Linuxu, potomek dedi vlastnos rodice ale ne obracene !
*/
return 0;
}

