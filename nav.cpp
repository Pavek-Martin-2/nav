#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // system()
#include <windows.h> // pro funkci delay();
using namespace std;

// nahrada za prikaz CD

// PWD
string getCurrentDir() {
    char buffer[MAX_PATH];
    DWORD len = GetCurrentDirectoryA(MAX_PATH, buffer);
    if (len == 0 || len > MAX_PATH) {
        return "";
    }
    return string(buffer);
}

// existuje cilovy adresar ?
bool directoryExists(const string& path) {
    DWORD attrib = GetFileAttributesA(path.c_str());
    return (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY));
}

// posune nahoru
string moveUp(string path, int levels) {
    for (int i = 0; i < levels; ++i) {
        // odstrani pripadne koncov lomtko (krome korene disku napr. "C:\")
        if (path.length() > 3 && path.back() == '\\') {
            path.pop_back();
        }
        size_t pos = path.find_last_of('\\');
        if (pos == string::npos) {
            break;
        }
        // pokud jsme u korene disku (napr. "C:\Slozka"), ponechame "C:\"
        if (pos == 2 && path[1] == ':') {
            path = path.substr(0,3);
            break;
        } else {
            path = path.substr(0,pos);
        }
    }
    return path;
}

int main(int argc, char* argv[]) {

    locale::global(locale(""));
    setlocale(LC_ALL, "");
	
    if (argc < 2) {
    	cerr<<"\nzadej v konzoli tento prikaz:\n";
    	cerr<<"chcp 1250 >nul && ";
    	cerr<<"doskey nav=for /f ";
    	cerr<<'"';
    	cerr<<"delims=";
    	cerr<<'"';
    	cerr<<" %i in (";
    	cerr<<"'";
    	//cerr<<"C:\\Users\\DELL\\Documents\\Dev-Cpp\\nav\\nav.exe";
    	//cerr<<"C:\\tools\\nav.exe";
    	cerr<<"nav.exe";
		cerr<<" $*') do @cd /d ";
		cerr<<'"';
    	cerr<<"%i";
    	cerr<<'"'<<endl;
    	cerr<<"\ncesta k souboru nav.exe musi byt v promenne PATH\n";
    	cerr<<"pokud tomu tak neni nahrad za plnou cestu napø. C:\\tools\\nav.exe\n";
        cerr<<"\npotom pro pouziti:\n";
        cerr<<"nav slozka\n";
        cerr<<"nav "<<'"'<<"nejaky adresar"<<'"'<<"\n";
		cerr<<"nav "<<'"'<<"Nová složka"<<'"'<<"\n";
        cerr<<"nav ..\n";
        Sleep(3000);
        return 1;
    }

    string mode = argv[1];
    string currentPath = getCurrentDir();
    string targetPath = currentPath;

    if (mode == "..") { // posunuje dolu jako prikaz "cd .."
        int levels = 1;
        targetPath = moveUp(currentPath, levels);
    } else {
        string subDir = argv[1];
        if (targetPath.back() != '\\') {
            targetPath += "\\";
        }
        targetPath += subDir;
    } 

    // kontrola existence cilove slozky
    if (!directoryExists(targetPath)) {
		cerr<<"chyba\n";
		Sleep(1000);
        return 1;
    }
    
    // osetreni chyby (jine nazli dve tecky na konci)
    int d_targetPath = targetPath.length();
    if (targetPath.substr(d_targetPath -1,1) == "."){
    cerr<<"chyba\n";	
	Sleep(1000);
    return 1;
    }
    
    cout<<'"'<<targetPath<<'"'<<endl; 
	return 0;	
}
