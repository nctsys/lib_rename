
/*
	Program: Rename
	Autor: Diego
	Data:  Dom 04 Set 2016 02:22:24 BRT 
	
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cstdlib>

using namespace std;

int main( int argc, char **argv )
{
    
    //constantes para identificação do programa
    const double version = 0.1;
    const string description = "A simple program to rename multiple files at once.";
    const string name = "Rename All";
    const string author = "Diego, 6b616c69h@gmail.com";
    const string date = "Sun 04 Set 2016 02:22:24";
    
    //constantes de cptacão de comandos e definição de limite de array
    const int MAX = 1024;
    const char *command;
    const char *dir;
    
    //variáveis iteradoras
    static int filescount = 0;
    char char_it;
    
    //variáveis para manipulação de arquivos
    fstream fs;
    FILE *_fs;
    string catchfname;
    char buff[MAX];
    
    //
    string fnewpath;
    string foldpath = "/tmp/oldnames";
    
    //"recebe" o comando e "transfere" para a variável command
    if( argv[1] != NULL ){ command = argv[1]; }
    else{ command = ""; }
    
    if( argv[2] != NULL ){ dir = argv[2]; }
    else{ dir = ""; }
    
    //
    if( strcmp( dir, "" ) == 0 ){;}
    else{ fnewpath = dir; fnewpath+= "newnames"; }    
    
    //Sequência de comandos aceitos ...
    
    //Valida o comando digitado
    if( strcmp( command, "--list" ) == 0 )
    { 
         if( strcmp( dir, "" ) == 0){ cout << "\n\tERROR: you must define the directory that contains the \"newnames\" file.\n" << endl; }
        else
        {
            //filescount = 0;
            string snewname[MAX];
            remove( fnewpath.c_str() );
            remove( foldpath.c_str() );

            //fs.open( fnewpath.c_str(), ios::out );
            //fs.open( foldpath.c_str(), ios::out );
            string catchfname2;

            string s = "ls \"";
            s+= dir;
            s+= "\"";

            _fs = popen( s.c_str(), "r" );
            while ( fgets( buff, sizeof buff, _fs))
            {
                catchfname2 = dir;
                catchfname = buff;
                catchfname2+= catchfname;

                snewname[filescount] = catchfname2;
                filescount++;
            }
            pclose( _fs );

            fs.open( fnewpath.c_str(), ios::out );
            if( fs.is_open() )
            {   
                for(int n = 0; n < filescount+1; n++)
                {
                    fs << snewname[n];
                }
            }
            else{ cout << "\nError: opening file.\nError Code:" << cerr << endl; }
            fs.close();

            fs.open( foldpath.c_str(), ios::out );
            if( fs.is_open() )
            {   
                for(int k = 0; k < filescount+1; k++)
                {
                    fs << snewname[k];
                }
            }
            else{ cout << "\nError: opening file.\nError Code:" << cerr << endl; }
            fs.close();
            
            cout << endl;
            cout << "\tTotal Files Listed: " << filescount << endl;
            
        }
    }
    else if( strcmp( command, "--rename") == 0 )
    {
        if( strcmp( dir, "" ) == 0){ cout << "\n\tERROR: you must define the directory that contains the \"newnames\" file.\n" << endl; }
        else
        {
            string s = "ls \"";
            s+= dir;
            s+= "\"";

            _fs = popen( s.c_str(), "r" );
            while ( fgets( buff, sizeof buff, _fs))
            {
                filescount++;
            }
            pclose( _fs );
            
            filescount-= 1;
            
            string *oldname = new string[ filescount ];
            string *newname = new string[ filescount ];

            fs.open( fnewpath.c_str(), ios::in );
            if( fs.is_open() )
            {  	
                for( int j = 0; j < filescount; j++ )
                {         
                    fs.getline(buff, MAX );

                    catchfname = buff;
                    newname[j] = catchfname;

                    //cout << newname[j] << endl;
                }
            }
            else
            {
                cout << "\nError _opening file. " << fnewpath << "\nError Code: " << cerr << "\n" << endl;
            }
            fs.close();

            fs.open( foldpath.c_str(), ios::in );
            if( fs.is_open() )
            {  	
                for( int j = 0; j < filescount; j++ )
                {         
                    fs.getline(buff, MAX );

                    catchfname = buff;
                    oldname[j] = catchfname;

                    //cout << oldname[j] << endl;
                }
            }
            else
            {
                cout << "\nError opening file.\nError Code: " << cerr << "\n" << endl;
            }
            fs.close();

            cout << "\tTotal Files Renamed: " << filescount << endl;
            
            for(int k = 0; k < filescount; k++ )
            {
                rename( oldname[k].c_str(), newname[k].c_str() );	
                //cout << "\nRename \"" << oldname[k] << "\" to \"" << newname[k] << "\" ";
            }

            remove( fnewpath.c_str() );
            remove( foldpath.c_str() );

            delete [] oldname;
            delete [] newname;

            newname = NULL;
            oldname = NULL;

            cout << endl;
        }
    }
    else if( strcmp( command, "--help" ) == 0 )
    {
        cout <<"\n  " << name << " " << version << "\n" << endl;
        cout << "Syntax: Rename [option] [path]\n\n  Options:\n" << endl;
        cout << "    --help\t-\tDisply this help text." << endl;
        cout << "    --list\t-\tList files to rename. " << endl;
        cout << "    --rename\t-\tRename all files (Must be used after --list)." << endl;
        cout << "    --version\t-\tDisplay info about this program" << endl;
        cout << "\n  Example: \n"<< endl;
        cout << "\ttype \"Rename --list /path/to/files/\" to create a list of files "<< endl;
        cout << "\ttype \"Rename --rename /pah/to/files/\" to rename the files. " << endl;
        cout << "\n  Usage:\n" << endl;
        cout << "\tEdit the file created by \"--list\" option, replacing the names that are listed for what you want.\n"
                "\tPlease do not change the sequence of the list and do not delete the folder list.\n"
                "\tIf you choose not to rename a particular file, leave it in the list unchanged.\n" << endl;
                

        cout << endl;
    }
    else if( strcmp( command, "--version" ) == 0 )
    {
        cout << endl;
        cout << "\tProgram name:\t" << name << endl;
        cout << "\tDescription:\t" << description << endl;
        cout << "\tVersion:\t" << version << endl;
        cout << "\tAuthor(s):\t" << author << endl;
	cout << "\tDate:\t" << date << endl;
        cout << endl;
    }
    else if( strcmp( command, "" ) == 0 ){ cout << "\nDigite ./Rename --help para mais informações.\n" << endl; }
    else { cout << "\nError: Command \"" << command << "\" not found.\n" << endl; }
    
    return 0;
}
