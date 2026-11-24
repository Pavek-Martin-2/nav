#include <iostream>
#include <windows.h>
using namespace std;

int main(){

string adresar = "testovaci_adresar";
//string adresar = "testovaci_adresarrrrrrrrr"; // testovaci radek
//string adresar = "Nová složka"; // test diakritiky v nazvu adresare
int navratovy_kod;
	
// adresar existoval, prikaz se proved ael nic se nepreplo
navratovy_kod = SetCurrentDirectoryA(adresar.c_str());
cout<<"navratovy kod prikazu 'cd testovaci_adresar' = "<<navratovy_kod<<endl;
/* 
tady je navrotovej kod 1, tzn. chyba
takze v terminalu odkud byl "SetCurrentDirectoryA_1.exe" spusten se prikaz neprovedl
a provedl se pouze interne zde, takze je to zase ze rodic nemuze zdedit vlastnost potomka
ale pouze naopak
dalsi vec, paklize adresar "testovaci_adresar" neexistuje, tedy neni se do ceho prepnout
pak bude navratovej kod 0, tzn. uspech, a udela se DIR adresare odkud byl
spustenej "SetCurrentDirectoryA_1.exe"
*/

navratovy_kod = system("dir");
cout<<"navratovy kod prikazu 'dir' = "<<navratovy_kod<<endl;
// a prikaz 'dir' je navratovy kod 0, cili uspech

system("pause");
return 0;
}

