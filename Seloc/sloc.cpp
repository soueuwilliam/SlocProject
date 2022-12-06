#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <iomanip>
#include <string.h>

using namespace std;

void printMenu(){
        cout << endl;
        cout << "SLOC 1.0 - Made by William and Carlos, as a project for Programming Language I - UFRN" << endl;
        cout << endl;
        cout << "Usage syntax: sloc [options] file/directory" << endl;
        cout << endl;
        cout << "Options:" << endl;
        cout << endl;
        cout << "-h/--help       Print this screen. (Ignored if any other commands are used)" << endl;
        cout << "-r              Search for file recursively within the provided directory." << endl;
        cout << "-s f/t/c/b/s/a  Order the resulting table in an ascending manner by: (f) file name, (t) file type, (c) commentary count," << endl;
        cout << "                (b) blank line count, (s) code line count or (a) all." << endl;
        cout << "-S f/t/c/b/s/a  Same as above, but in descending order." << endl;
}

struct file // struct usado para armazenar as informações de todos os arquivos analisados
{
    string nameFile;
    string typefile;
    int ncoments;
    int nblankLines;
    int ncodeLines;
    int allLines;
    
};

void insertfiles(vector<file> &filesVector,string insertNameFile, string insertFtypefile, int insertNComents, int insertNBlanckLines, int insertNCodeLines, int insertAllLines){
        file insertData;
        insertData.nameFile = insertNameFile;
        insertData.typefile = insertFtypefile;
        insertData.ncoments = insertNComents;
        insertData.nblankLines = insertNBlanckLines;
        insertData.ncodeLines = insertNCodeLines;
        insertData.allLines = insertAllLines;
        filesVector.push_back(insertData);
}

bool sortNameFile(file a , file b){
    return a.nameFile < b.nameFile;
}
bool sortTypeFile(file a , file b){
    return a.typefile < b.typefile;
}
bool sortComments(file a , file b){
    return a.ncoments < b.ncoments;
}
bool sortBlankLines(file a , file b){
    return a.nblankLines < b.nblankLines;
}
bool sortCodeLines(file a , file b){
    return a.ncodeLines < b.ncodeLines;
}
bool sortTotal(file a , file b){
    return a.allLines < b.allLines;
}

float porcentCalc(int a, int b){
    float x = (float) a;
    float y = (float) b;

    return y*100/x;
}

void showVector(vector<file> vector_files, int sizecolun, int &TOTCOM, int &TOTBLANK,  int &TOTCODE, int &TOTTOT){
        int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;

        for (int i = 0; i < vector_files.size(); i++)
        {
            if(to_string(vector_files[i].ncoments).length()>temp1){
                temp1 = to_string(vector_files[i].ncoments).length();
            }
            if(to_string(vector_files[i].nblankLines).length()>temp2){
                temp2 = to_string(vector_files[i].nblankLines).length();
            }
            if(to_string(vector_files[i].ncodeLines).length()>temp3){
                temp3 = to_string(vector_files[i].ncodeLines).length();
            }
            if(to_string(vector_files[i].allLines).length()>temp4){
                temp4 = to_string(vector_files[i].allLines).length();
            }
        }

        temp1+=10;
        temp2+=6;
        temp3+=10;
        temp4+=10;

        cout << endl;
        cout << "Files processed: " << vector_files.size() << endl;
        cout << setw(sizecolun+(temp1+6)+(temp2+7)+(temp3+8)+temp4+9) << setfill('-') << "-" << setfill(' ') << endl;
        cout << setw(sizecolun) << left << "File Name"   ;
        cout << setw(15) << left << "Language"    ;
        cout << setw(temp1+6) << left << "Comments"    ;
        cout << setw(temp2+7) << left << "Blank"       ;
        cout << setw(temp3+8) << left << "Code"        ;
        cout << setw(temp4) << left << "Total"       ;
        cout << endl;
        cout << setw(sizecolun+(temp1+6)+(temp2+7)+(temp3+8)+temp4+9) << setfill('-') << "-" << setfill(' ') << endl;

        for (int i = 0; i < vector_files.size(); i++)
        {
            cout << setw(sizecolun) << left << vector_files[i].nameFile;
            cout << setw(15) << left << vector_files[i].typefile;
            cout << vector_files[i].ncoments << fixed << setprecision(1) << " (" << porcentCalc(vector_files[i].allLines, vector_files[i].ncoments) << setw(temp1) << left << "%)";
            cout << vector_files[i].nblankLines << " (" << porcentCalc(vector_files[i].allLines, vector_files[i].nblankLines) << setw(temp2) << left << "%)";
            cout << vector_files[i].ncodeLines << " (" << porcentCalc(vector_files[i].allLines, vector_files[i].ncodeLines) << setw(temp3) << left << "%)";
            cout << setw(temp4) << left << vector_files[i].allLines;
            cout <<endl;

            TOTCOM = TOTCOM + vector_files[i].ncoments;
            TOTBLANK = TOTBLANK + vector_files[i].nblankLines;
            TOTCODE = TOTCODE + vector_files[i].ncodeLines;
            TOTTOT = TOTTOT + vector_files[i].allLines;
        }

        if(vector_files.size()>1){
            cout << setw(sizecolun+(temp1+6)+(temp2+7)+(temp3+8)+temp4+9) << setfill('-') << "-" << setfill(' ') << endl;
            cout << setw(sizecolun) << left << "SUM:";
            cout << setw(15) << left << " ";
            cout << setw(temp1+6) << left << TOTCOM;
            cout << setw(temp2+7) << left << TOTBLANK;
            cout << setw(temp3+8) << left << TOTCODE;
            cout << setw(temp4+9) << left << TOTTOT;
            cout << endl;
            cout << setw(sizecolun+(temp1+6)+(temp2+7)+(temp3+8)+temp4+9) << setfill('-') << "-" << setfill(' ') << endl;
        }else{
           cout << setw(sizecolun+(temp1+6)+(temp2+7)+(temp3+8)+temp4+9) << setfill('-') << "-" << setfill(' ') << endl; 
        }
    } 

bool validFile(string &arquivo, string &fileT){
    int n = arquivo.find(".");
    string type = arquivo.substr(n+1);

    if(type=="cpp"){
        fileT = "C++";
    }else if(type=="c"){
        fileT = "C";
    }else if(type=="h"){
        fileT = "C header";
    }else if(type=="hpp"){
        fileT = "C++ header";
    }else{
        return false;
    }
    return true;
}

void readFile(string &arquivo, string &fileT, int &linhasCod, int &linhasVaz, int &linhasCom, int &linhasTot){
    ifstream newfile;

    if(!validFile(arquivo, fileT)){
        return;
    }

    newfile.open(arquivo);
    if(newfile.is_open()){
        bool code, vaz, com, commentaryMode = false;
        string texto;

        while(getline(newfile, texto)){ // loop que percorre o arquivo inteiro (linha a linha)
            linhasTot++;

            code = false;
            com = false;
            vaz = true;

            if(texto[0]=='\0' && commentaryMode==true){ // se a linha começar com \0, adiciona +1 pra linhasVaz pois é uma linha em branco
                linhasCom++;
            }else if(texto[0]=='\0' && commentaryMode==false){
                linhasVaz++;
            }else{ // se não, a linha é percorrida para identificar se contém código/comentário ou se é vazia mesmo
                for(int i=0; i<texto.length(); i++){

                    if(commentaryMode==true){ // se o modo comentário estiver ligado, tudo que não for vazio vira comentário
                        if(texto[i]=='*' && texto[i+1]=='/'){
                            com = true;
                            vaz = false;
                            commentaryMode = false;
                            i++;
                        }else if(texto[i]!=' ' && texto[i]!='\0'){
                            com = true;
                            vaz = false;
                        }

                    }else if(commentaryMode==false){ // se o modo comentário não estiver ligado, são distinguidos código, comentário, e linhas vazias
                        if(texto[i]=='/' && texto[i+1]=='/'){
                            com = true;
                            vaz = false;
                            break;
                        }else if(texto[i]=='/' && texto[i+1]=='*'){
                            com = true;
                            vaz = false;
                            commentaryMode = true;
                        }else if(texto[i]!=' ' && texto[i]!='\0'){
                            code = true;
                            vaz = false;
                        }
                    }
                }

                // após a linha ser analisada, a função agora sabe se ela contém códigos/comentários ou se é vazia, e agora ela
                // faz a adição aos contadores pertencentes a esse arquivo

                if(code){
                    linhasCod++;
                }
                if(com){
                    linhasCom++;
                }
                if(vaz){
                    linhasVaz++;
                }
            }
        }

        newfile.close(); // o arquivo é fechado e os números são devidamente despachados 
    }
}


int main(int argc, char *argv[]){
    int TOTCOM = 0, TOTBLANK = 0, TOTCODE = 0, TOTTOT = 0;
    size_t sizeColumn = 0;
    string arquivo, tipo, path = argv[argc-1];

    vector<file> listofstrutcs;

    if(argc==1 || (argc==2 && strcmp(argv[1], "-h")==0) || (argc==2 && strcmp(argv[1], "--help")==0)){
        printMenu(); // se o programa for inicado sem argumentos ou com -h/--help, ele imprime o menu de ajuda
    }else{
        if(validFile(path, tipo)){ // se o argumento final for apenas um arquivo, esse único arquivo é lido

            int linhacodigo = 0, vazio = 0,  linhacomentario = 0, total = 0;
            int n = path.find_last_of("\\");
            arquivo = path;

            readFile(arquivo, tipo, linhacodigo, vazio, linhacomentario, total);

            arquivo = path.substr(n+1);
            sizeColumn = arquivo.length();

            insertfiles(listofstrutcs,arquivo,tipo,linhacomentario,vazio,linhacodigo,total);

        }else{ // se for um diretório, o diretório inteiro é lido

            for (const auto & entry : filesystem::directory_iterator(path)){
                int linhacodigo = 0, vazio = 0,  linhacomentario = 0, total = 0;
                arquivo = entry.path().string();

                readFile(arquivo, tipo, linhacodigo, vazio, linhacomentario, total);

                arquivo = entry.path().filename().string();

                if(entry.path().filename().string().length()>sizeColumn){
                    sizeColumn = entry.path().filename().string().length();
                }

                if(validFile(arquivo, tipo)){
                    insertfiles(listofstrutcs,arquivo,tipo,linhacomentario,vazio,linhacodigo,total);
                }
            }
        }
        cout << "Sort com nomes" << endl;
        sort(listofstrutcs.begin(),listofstrutcs.end(),sortNameFile);
        showVector(listofstrutcs, sizeColumn+3, TOTCOM, TOTBLANK, TOTCODE, TOTTOT);
        cout << "Sort com tipo de arquivo" << endl;
        sort(listofstrutcs.begin(),listofstrutcs.end(),sortTypeFile);
        showVector(listofstrutcs, sizeColumn+3, TOTCOM, TOTBLANK, TOTCODE, TOTTOT);
        cout << "Sort com comentário";
        sort(listofstrutcs.begin(),listofstrutcs.end(),sortComments);
        showVector(listofstrutcs, sizeColumn+3, TOTCOM, TOTBLANK, TOTCODE, TOTTOT);
        cout << "Sort com blank";
        sort(listofstrutcs.begin(),listofstrutcs.end(),sortBlankLines);
        showVector(listofstrutcs, sizeColumn+3, TOTCOM, TOTBLANK, TOTCODE, TOTTOT);
        cout << "Sort com code";
        sort(listofstrutcs.begin(),listofstrutcs.end(),sortCodeLines);
        showVector(listofstrutcs, sizeColumn+3, TOTCOM, TOTBLANK, TOTCODE, TOTTOT);
        cout << "Sort com total";
        sort(listofstrutcs.begin(),listofstrutcs.end(),sortTotal);
        showVector(listofstrutcs, sizeColumn+3, TOTCOM, TOTBLANK, TOTCODE, TOTTOT);
        
    }
    
    return 0;
}