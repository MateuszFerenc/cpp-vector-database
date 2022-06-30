/*


db_vector.cpp
Mateusz Ferenc 3AT


*/
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <ctype.h>
#include <regex>		//Importatnt!!!! C++11 compiler needed!
#include <iomanip>
#include <locale.h>
using namespace std;

#define get_cin(in)		cin>>in; if(cin.fail()){ cout<<"\nInput error: Wrong data type\n"; system("pause"); return 3;}
#define get_line(in)	cin.clear();  fflush(stdin); getline(cin, in); if(cin.fail()){ cout<<"\nInput error: Wrong data type\n"; system("pause"); return 3;}
#define operations_defined 	(3) - 1
#define check_goto(check, where, info)	if(check){ cout<<info<<"\n"; goto where; }
#define cmd_list1 "Available commands:\n\nWRITE - to write data\nREAD - to read data\nCLR - clear screen\nHELP - show commands\nEND - aborts program execution\n"
#define cmd_list2 "Available commands:\n\nBOOK - Bookshelf\nREPAIR - Repairs list\nHOME - Home equipment\nCLR - clear screen\nHELP - show commands\nEND - aborts program execution\nEXIT - exit write mode\n"

//I hope it's obvious
struct book_{
	int index;
	string title;
	string author;
	int no_pages;
	float price;
};

//Upper structure members for search in querries
const string book_columns[5] = {
	"INDEX",
	"TITLE",
	"AUTHOR",
	"NO_PAGES",
	"PRICE"
};

//I hope it's obvious
struct repair_{
	int index;
	string type;
	string info;
	string objections;
	float cost;
	int days;
};

//Upper structure members for search in querries
const string repair_columns[6] = {
	"INDEX",
	"TYPE",
	"INFO",
	"OBJ",
	"TIME",
	"COST"
};

//I hope it's obvious
struct home_{
	int index;
	string object_name;
	string description;
	float price;
	int days_2buy;
};

//Upper structure members for search in querries
const string home_columns[5] = {
	"INDEX",
	"OBJ_NAME",
	"DSC",
	"DAYS_LEFT",
	"PRICE"
};

//Available querries
const string DB_querries[] = {
	"SEARCH",
	"FOR",
	"WHERE",
	"BOOK",
	"REPAIR",
	"HOME",
	"ALL",
	"INDEX",
	"TITLE",
	"AUTHOR",
	"NO_PAGES",
	"PRICE",
	"TYPE",
	"INFO",
	"OBJ",
	"COST",
	"OBJ_NAME",
	"DSC",
	"DAYS_LEFT",
	"TIME"
};

//Smoe variables, for various data types :)
int int_in, int_in1, int_in2, int_in3, int_temp;
string string_in, string_temp, string1, string2;
char char_in;
double double_in;

//I could give members of this stucture other names..
struct db{
	string first;
	string source;
	string second;
	string via;
	string last;
	string dest;
};

//It's useful for string substraction
size_t pos;

//Gorgeous vectors..
vector <home_> home;
vector <repair_> repair;
vector <book_> book;

//Files, files...
fstream books;
fstream repairs;
fstream homes;

//Down there
void atexit_handler(void){
	books.close();
	repairs.close();
	homes.close();
}

int main(void){
	//Soooo, for some reasons it's nice to have certanity of things were done
	atexit(atexit_handler);
	
	book_ b;
	repair_ r;
	home_ h;
	
	book.clear();
	repair.clear();
	home.clear();
	
	//Default index values, if no files or empty when writing data index is set to 0
	b.index = -1;
	r.index = -1;
	h.index = -1;
	
	//It's obvious what it does, I hope...
	system("COLOR 3F");
	system("TITLE INFORMATYKA ZSL");
	
	//Strucure for holding querries
	db database;
	
	//This value have several uses, now it'll store parameters of files opening success (0) or failure (any value)
	int_temp = 0;
	
	//For better performance
	keybd_event( VK_F11, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );
	keybd_event( VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );
	
	//Open files to read them into vectors
	books.open("books.txt", ios::in);
	if(!books){
		cout<<"Info: File books.txt does not exist!\n";
		int_temp |= 1;
	}
	repairs.open("repairs.txt", ios::in);
	if(!repairs){
		cout<<"Info: File repairs.txt does not exist!\n";
		int_temp |= 2;
	}
	homes.open("homes.txt", ios::in);
	if(!homes){
		cout<<"Info: File homes.txt does not exist!\n";
		int_temp |= 4;
	}
	//read files to vectors
	//If file does not exist it cannot be read, so files that not exist are omited
	if((int_temp&1) == 0){
		string_in = "";
		string * temp_string = new string [6];
		books.seekg(0, books.end);
		int_in2 = books.tellg();
		books.seekg(0, books.beg);
		char * buff0 = new char [int_in2];
		books.read(buff0, int_in2);
		if(books.good()){
			cout<<"Info: books.txt readed succesfully!\n";
			if(int_in2>5){
				int_in = int_in1 = 0;
				for(;int_in <= int_in2;int_in++){
					string_temp = "";
					string_temp = buff0[int_in];
					if(string_temp == "*"){
						temp_string[int_in1++] = string_in;
						string_in = "";
						if(int_in1 == 5){
							int_in1 = 0;
							b.index = atoi(temp_string[0].c_str());
							b.title = temp_string[1];
							b.author = temp_string[2];
							b.price = atof(temp_string[3].c_str());
							b.no_pages = atoi(temp_string[4].c_str());
							book.push_back(b);
						}
						continue;
					}
					string_in += buff0[int_in];
				}
			}
		} else
			cout<<"Info: Got error while reading books.txt\n";
			
		delete[] buff0;
		delete[] temp_string;
		books.close();
	}
	if(((int_temp>>1)&1) == 0){
		string_in = "";
		string * temp_string = new string [6];
		repairs.seekg(0, repairs.end);
		int_in2 = repairs.tellg();
		repairs.seekg(0, repairs.beg);
		char * buff1 = new char [int_in2];
		repairs.read(buff1, int_in2);
		if(repairs.good()){
			cout<<"Info: repairs.txt readed succesfully!\n";
			if(int_in2>5){
				int_in = int_in1 = 0;
				for(;int_in <= int_in2;int_in++){
					string_temp = "";
					string_temp = buff1[int_in];
					if(string_temp == "*"){
						temp_string[int_in1++] = string_in;
						string_in = "";
						if(int_in1 == 6){
							int_in1 = 0;
							r.index = atoi(temp_string[0].c_str());			
							r.type = temp_string[1];
							r.info = temp_string[2];
							r.objections = temp_string[3];
							r.cost = atof(temp_string[4].c_str());	
							r.days = atoi(temp_string[5].c_str());
							repair.push_back(r);
						}
						continue;
					}
					string_in += buff1[int_in];
				}
			}
		} else
			cout<<"Info: Got error while reading repairs.txt\n";
			
		delete[] buff1;
		delete[] temp_string;
		repairs.close();
	}
	if(((int_temp>>2)&1) == 0){
		string_in = "";
		string * temp_string = new string [6];
		homes.seekg(0, homes.end);
		int_in2 = homes.tellg();
		homes.seekg(0, homes.beg);
		char * buff2 = new char [int_in2];
		homes.read(buff2, int_in2);
		if(homes.good()){
			cout<<"Info: homes.txt readed succesfully!\n";
			if(int_in2>5){
				int_in = int_in1 = 0;
				for(;int_in <= int_in2;int_in++){
					string_temp = "";
					string_temp = buff2[int_in];
					if(string_temp == "*"){
						temp_string[int_in1++] = string_in;
						string_in = "";
						if(int_in1 == 5){
							int_in1 = 0;
							h.index = atoi(temp_string[0].c_str());	
							h.object_name = temp_string[1];
							h.description = temp_string[2];
							h.price = atof(temp_string[3].c_str());
							h.days_2buy = atoi(temp_string[4].c_str());
							home.push_back(h);
						}
						continue;
					}
					string_in += buff2[int_in];
				}
			}
		} else
			cout<<"Info: Got error while reading homes.txt\n";
			
		delete[] buff2;
		delete[] temp_string;
		homes.close();
	}
	int_temp = 0;
	
	//Reopen files to place pointer at end of files
	books.open("books.txt", ios::app);
	if(!books){
		cout<<"Critical error: File books.txt does not exist!\n";
		system("pause"); 
		return 3;
	}
	repairs.open("repairs.txt", ios::app);
	if(!repairs){
		cout<<"Critical error: File repairs.txt does not exist!\n";
	 	system("pause"); 
	 	books.close();
		return 3;
	}
	homes.open("homes.txt", ios::app);
	if(!homes){
		cout<<"Critical error: File homes.txt does not exist!\n";
		system("pause");
		books.close();
		repairs.close(); 
		return 3;
	}
	//Remember sleep is very important
	Sleep(1500);
	system("cls");
	cout<<"****File archive and database - Copyright 2020 - Mateusz Ferenc****\n\n";
	cout<<cmd_list1;
	idx_txt:
	cout<<"READY.\n>";
	get_cin(string_in);
	//Let's see what user gave to us
	if(strcasecmp(string_in.c_str(), "end") == 0){
		//See ya later alligator ;)
		cout<<"\nBye\n";
		system("pause");
		return 0;
	} else if(strcasecmp(string_in.c_str(), "help") == 0){
		//Get some help, forgetful boi
		cout<<cmd_list1;
		goto idx_txt;
	} else if(strcasecmp(string_in.c_str(), "clr") == 0){
		//Tabula rasa
		system("cls");
		goto idx_txt;
	} else if(strcasecmp(string_in.c_str(), "write") == 0){
		/*			Do you remember
		The twenty first night of September?			*/
		write_:
		system("cls");
		cout<<cmd_list2;
		write_txt:
		cout<<"READY.\n:(";
		get_cin(string_in);
		//Again, let's see..
		if(string_in == "END"){
			//See ya later alligator ;)
			cout<<"\nBye\n";
			system("pause");
			return 0;
		}else if(strcasecmp(string_in.c_str(), "book") == 0){
			//You little bookworm ;)
			do{				
				b.index++;
				cout<<"\nBook with "<<b.index<<" index.\n";
			
				book_enter:
			
				cout<<"Enter book title (string)?";
				get_line(string_in);
				b.title = string_in;
			
				cout<<"Enter book author (string)?";
				get_line(string_in);
				b.author = string_in;
			
				cout<<"Enter book price (xxx.yy)?";
				get_cin(double_in);
				b.price = double_in;
		
				cout<<"Enter amount of book pages (number)?";
				get_cin(int_in1);
				b.no_pages = int_in1;
		
				cout<<"\nCheck the correctness of entered data..\n";
				cout<<"Do you want to reenter data? Y/N?";
				get_cin(string_in);
				if(strcasecmp(string_in.c_str(), "y") == 0) goto book_enter;
			
				books<<b.index<<"*"<<b.title<<"*"<<b.author<<"*"<<b.price<<"*"<<b.no_pages<<"*";
				
				book.push_back(b);
				
				cout<<"Enter next book or quit? E/Q?";
				get_cin(string_in);
				if(strcasecmp(string_in.c_str(), "q") == 0) {
					break;
				}
			} while(1);	
			goto write_txt;
			//Ba de ya say do you remember
		} else if(strcasecmp(string_in.c_str(), "repair") == 0){
			//Ohh handyman
			do{
				r.index++;		
				cout<<"\nRepair with "<<r.index<<" index.\n";
		
				repair_enter:
		
				cout<<"Enter repair type (string)?";
				get_line(string_in);
				r.type = string_in;
		
				cout<<"Enter repair info (string)?";
				get_line(string_in);
				r.info = string_in;
			
				cout<<"Enter repair objections (string)?";
				get_line(string_in);
				r.objections = string_in;
		
				cout<<"Enter repair cost (xxx.yy)?";
				get_cin(double_in);
				r.cost = double_in;
				
				cout<<"Enter time to repair (days) (number, -1 if not urgent)?";
				get_cin(int_in1);
				r.days = int_in1;
		
				cout<<"\nCheck the correctness of entered data..\n";
				cout<<"Do you want to reenter data? Y/N?";
				get_cin(string_in);
				if(strcasecmp(string_in.c_str(), "y") == 0) goto repair_enter;
				
				repairs<<r.index<<"*"<<r.type<<"*"<<r.info<<"*"<<r.objections<<"*"<<r.cost<<"*"<<r.days<<"*";
				
				repair.push_back(r);
				
				cout<<"Enter next repair or quit? E/Q?";
				get_cin(string_in);
				if(strcasecmp(string_in.c_str(), "q") == 0) {
					break;
				}
			} while(1);
			goto write_txt;
			//Ba de ya dancing in September
		}else if(strcasecmp(string_in.c_str(), "home") == 0){
			//Don't forget about your spaaaaceeee!!!
			do{
				h.index++;
				cout<<"\nHome equipment with "<<h.index<<" index.\n";
		
				home_enter:
		
				cout<<"Enter object name (string)?";
				get_line(string_in);
				h.object_name = string_in;
				
				cout<<"Enter object description (string)?";
				get_line(string_in);
				h.description = string_in;
		
				cout<<"Enter oject price (xxx.yy)?";
				get_cin(double_in);
				h.price = double_in;
			
				cout<<"Enter days to buy object (number, , -1 if not urgent)?";
				get_cin(int_in1);
				h.days_2buy = int_in1;
		
				cout<<"\nCheck the correctness of entered data..\n";
				cout<<"Do you want to reenter data? Y/N?";
				get_cin(string_in);
				if(strcasecmp(string_in.c_str(), "y") == 0) goto home_enter;
		
				homes<<h.index<<"*"<<h.object_name<<"*"<<h.description<<"*"<<h.price<<"*"<<h.days_2buy<<"*";
				
				home.push_back(h);
		
				cout<<"Enter next home equipment or quit? E/Q?";
				get_cin(string_in);
				if(strcasecmp(string_in.c_str(), "q") == 0) {
					break;
				}
			} while(1);
			goto write_txt;
			//Ba de ya never was a cloudy day
		} else if(strcasecmp(string_in.c_str(), "exit") == 0)
			//Don't stop me now!
			goto idx_txt;
		else if(strcasecmp(string_in.c_str(), "help") == 0){
			//Get some help, forgetful boi
			cout<<cmd_list2;
			goto write_txt;
		} else if(strcasecmp(string_in.c_str(), "clr") == 0){
			//Tabula rasa
			system("cls");
			goto write_txt;
		} else {
			//Boiiii what just you did?!
			cout<<"\nInput error: No operations linked with "<<string_in<<"\n";
			goto write_txt;
		}
	} else if(strcasecmp(string_in.c_str(), "read") == 0){
		read_:
		system("cls");
		cout<<"Available DataBase querries are:\n";
		for(int all = 0; all < (sizeof(DB_querries)/sizeof(*DB_querries)); all++){
			cout<<DB_querries[all]<<"\n";
		}
		cout<<"\n\n\
BOOK - table that contains books\n\
REPAIR - table that contains repairs\n\
HOME - table that contains home equipment\n\
ALL - all tables\n\n\
Usage:\n\
SEARCH <table> FOR <column> - looking for column in table\n\
SEARCH <table> FOR <column> WHERE expression - looking for column with expression in table\n\
SEARCH <table> - list <table> data(If a is ALL, all content of db is listed)\n\
HELP - show commands\n\
CLR - clear screen\n\
EXPRESSIONS - show available epressions in queries\n\
END - abort program execution\n\
EXIT - exit read mode\n";
		db_q:
		cout<<"\nREADY.\n:)";
		get_line(string_in)
		pos = 0;
		int_in3 = 0;
		pos = string_in.find(DB_querries[0]);
		if(pos != 0){
			if(strcasecmp(string_in.substr(0, 3).c_str(), "end") == 0){
				//See ya later alligator ;)
				cout<<"\nBye\n";
				system("pause");
				return 0;
			} else if(strcasecmp(string_in.substr(0, 4).c_str(), "exit") == 0)
				//Don't stop me now!
				goto idx_txt;
			else if(strcasecmp(string_in.substr(0, 4).c_str(), "help") == 0)
				//Get some help, forgetful boi
				goto read_;
			else if(strcasecmp(string_in.substr(0, 3).c_str(), "clr") == 0){
				//Tabula rasa
				system("cls");
				goto db_q;
			} else if(strcasecmp(string_in.substr(0, 11).c_str(), "expressions") == 0){
				//Now u can express yourself
				cout<<"=value - equal to value (number or text, case sensitive)\n|value - contains value (number or text, case sensitive)\n-value - except value (number or text, case sensitive)\n<value - less than value (ineffective with text)\n>value - higher than value (ineffective with text)\n";
				goto db_q;
			} else check_goto(1, db_q, "Input error: Incorrect command or request (no SEARCH)!");
		}
		database.first = string_in.substr(pos, DB_querries[0].size());
		string_in.erase(0, DB_querries[0].size() + 1);
		for(int i = 0; i <= 3; i++){
			pos = string_in.find(DB_querries[i + 3]);
			if(pos == 0){
				database.source = string_in.substr(pos, DB_querries[i + 3].size());
				string_in.erase(0, DB_querries[i + 3].size() + 1);
				break;
			}
		}
		check_goto((pos != 0), db_q, "Input error: Incorrect request (wrong <table>)!")
		if(string_in.empty()){
			database.dest = database.second = database.via = database.last = "-";
		}else {
			pos = string_in.find(DB_querries[1]);
			check_goto((pos != 0), db_q, "Input error: Incorrect request (no FOR)!")
			database.second = string_in.substr(pos, DB_querries[1].size());
			string_in.erase(0, DB_querries[1].size() + 1);
			for(int i = 0; i <= 12; i++){
				pos = string_in.find(DB_querries[i + 7]);
				if(pos == 0){
					database.via = string_in.substr(pos, DB_querries[i + 7].size());
					string_in.erase(0, DB_querries[i + 7].size() + 1);
					break;
				}
			}
			check_goto((pos != 0), db_q, "Input error: Incorrect request (wrong <column>)!")
			if(string_in.empty()){
				database.dest = database.last = "-";	
			}else {
				pos = string_in.find(DB_querries[2]);
				check_goto((pos != 0), db_q, "Input error: Incorrect request (no WHERE)!\n")
				database.last = string_in.substr(pos, DB_querries[2].size());
				string_in.erase(0, DB_querries[2].size() + 1);
				check_goto(string_in.empty(), db_q, "Input error: Empty expression!\n")
				database.dest = string_in;
				regex expr("([-<>|=]{1})([[:graph:]]*)", regex_constants::extended);
				smatch match;
				check_goto(!(regex_match(database.dest, match, expr)), db_q, "Input error: Incorrect expression\n");
				string1 = match[1];
				string2 = match[2];
			}
		}
		int_in = 0;
		if((database.source == "BOOK")|(database.source == "ALL")){
			int_temp = b.index;
			smatch match;
			cout<<"BOOK table contents:\n";
			if(database.second != "-"){
				for(auto column : book_columns){
					pos = database.via.find(column);
					if(pos == 0) break;
				}
				if(pos != 0) int_temp = -2;
				if((database.last != "-")&(int_temp != -2)){
					if(string_in != "-"){
					}	else	check_goto(1, db_q, "Critical error: Unexpected error!");
				}
			}
			if(int_temp > -1){
				unsigned int * columns_width = new unsigned int [(sizeof(book_columns)/sizeof(*book_columns)) - 1];
				unsigned int * row_present = new unsigned int [book.size()];
				int_in = 0;
				int_in2 = 0;
				for (auto column : book_columns){
					columns_width[int_in] = column.size() + 2;
					int_in++;
				}
				for (auto b_ : book) {
					int_in1 = (database.last == "-")? 1 : 0;
					if((database.via == book_columns[0])&(int_in1 != 1)){
						if(string1 == "="){
							regex expression(string2);
							if(regex_match(to_string(b_.index), expression))
								int_in1 = 1;
						} else if(string1 == "|"){
							regex expression(string2, regex_constants::icase);
							if(regex_search(to_string(b_.index), expression))
								int_in1 = 1;
						} else if(string1 == "-"){
							regex expression(string2);
							if(regex_search(to_string(b_.index), expression))
								int_in1 = 0;
							else 
								int_in1 = 1;
						} else if(string1 == "<"){
							regex expr("[[:digit]]");
							if(regex_match(string2, expr)){
								if(b_.index < stoi(string2))
									int_in1 = 1;
								else
									int_in1 = 0;
							} else {
								int_in1 = 0;
							}
						} else if(string1 == ">"){
							regex expr("[[:digit]]");
							if(regex_match(string2, expr)){
								if(b_.index > stoi(string2))
									int_in1 = 1;
								else
									int_in1 = 0;
							} else {
								int_in1 = 0;
							}
						} else
							int_in1 = 0;
					}
					if((database.via == book_columns[1])&(int_in1 != 1)){
						if(string1 == "="){
							regex expression(string2);
							if(regex_match(b_.title, expression))
								int_in1 = 1;
						} else if(string1 == "|"){
							regex expression(string2, regex_constants::icase);
							if(regex_search(b_.title, expression))
								int_in1 = 1;
						} else if(string1 == "-"){
							regex expression(string2);
							if(regex_search(b_.title, expression))
								int_in1 = 0;
							else 
								int_in1 = 1;
						} else if(string1 == "<")
							int_in1 = 0;
						else if(string1 == ">")
							int_in1 = 0;
						else
							int_in1 = 0;
					}
					if((database.via == book_columns[2])&(int_in1 != 1)){
						if(string1 == "="){
							regex expression(string2);
							if(regex_match(b_.author, expression))
								int_in1 = 1;
						} else if(string1 == "|"){
							regex expression(string2, regex_constants::icase);
							if(regex_search(b_.author, expression))
								int_in1 = 1;
						} else if(string1 == "-"){
							regex expression(string2);
							if(regex_search(b_.author, expression))
								int_in1 = 0;
							else 
								int_in1 = 1;
						} else if(string1 == "<")
							int_in1 = 0;
						else if(string1 == ">")
							int_in1 = 0;
						else
							int_in1 = 0;
					}
					if((database.via == book_columns[3])&(int_in1 != 1)){
						if(string1 == "="){
							regex expression(string2);
							if(regex_match(to_string(b_.no_pages), expression))
								int_in1 = 1;
						} else if(string1 == "|"){
							regex expression(string2, regex_constants::icase);
							if(regex_search(to_string(b_.no_pages), expression))
								int_in1 = 1;
						} else if(string1 == "-"){
							regex expression(string2);
							if(regex_search(to_string(b_.no_pages), expression))
								int_in1 = 0;
							else 
								int_in1 = 1;
						} else if(string1 == "<"){
							regex expr("[[:digit]]");
							if(regex_match(string2, expr)){
								if(b_.no_pages < stoi(string2))
									int_in1 = 1;
								else
									int_in1 = 0;
							} else {
								int_in1 = 0;
							}
						} else if(string1 == ">"){
							regex expr("[[:digit]]");
							if(regex_match(string2, expr)){
								if(b_.no_pages < stoi(string2))
									int_in1 = 1;
								else
									int_in1 = 0;
							} else {
								int_in1 = 0;
							}
						} else
							int_in1 = 0;
					}
					if((database.via == book_columns[4])&(int_in1 != 1)){
						if(string1 == "="){
							regex expression(string2);
							if(regex_match(to_string(b_.price), expression))
								int_in1 = 1;
						} else if(string1 == "|"){
							regex expression(string2, regex_constants::icase);
							if(regex_search(to_string(b_.price), expression))
								int_in1 = 1;
						} else if(string1 == "-"){
							regex expression(string2);
							if(regex_search(to_string(b_.price), expression))
								int_in1 = 0;
							else 
								int_in1 = 1;
						} else if(string1 == "<"){
							regex expr("[[:digit]]");
							if(regex_match(string2, expr)){
								if(b_.price < stoi(string2))
									int_in1 = 1;
								else
									int_in1 = 0;
							} else {
								int_in1 = 0;
							}
						} else if(string1 == ">"){
							regex expr("[[:digit]]");
							if(regex_match(string2, expr)){
								if(b_.price < stoi(string2))
									int_in1 = 1;
								else
									int_in1 = 0;
							} else {
								int_in1 = 0;
							}
						} else
							int_in1 = 0;
					}
					row_present[int_in2] = 0;
					if(int_in1 == 1){
						if(to_string(b_.index).size() > columns_width[0]){
							columns_width[0] = to_string(b_.index).size() + 2;
						}
						if(b_.title.size() > columns_width[1]){
							columns_width[1] = b_.title.size() + 2;
						}
						if(b_.author.size() > columns_width[2]){
							columns_width[2] = b_.author.size() + 2;
						}
						if(to_string(b_.no_pages).size() > columns_width[3]){
							columns_width[3] = to_string(b_.no_pages).size() + 2;
						}
						row_present[int_in2] = 1;
						int_in1 = 0;
					}
					int_in2++;
    			}
    			int_in = 0;
    			for (auto col : book_columns){
    				cout<<col;
    				for(int i = 0; i <= columns_width[int_in] - book_columns[int_in].size(); i++){
    					cout<<" ";
					}
					int_in++;
				}
				cout<<"\n";
				int_in2 = 0;
    			for (auto b_ : book){
    				if(row_present[int_in2] == 0){
    					int_in2++;
    					continue;
					}
    				cout<<b_.index;
    				for(int i = 0; i <= columns_width[0] - to_string(b_.index).size(); i++){
    					cout<<" ";
					}
					cout<<b_.title;
    				for(int i = 0; i <= columns_width[1] - b_.title.size(); i++){
    					cout<<" ";
					}
					cout<<b_.author;
    				for(int i = 0; i <= columns_width[2] - b_.author.size(); i++){
    					cout<<" ";
					}
					cout<<b_.no_pages;
    				for(int i = 0; i <= columns_width[3] - to_string(b_.no_pages).size(); i++){
    					cout<<" ";
					}
					cout<<fixed<<setprecision(2)<<b_.price<<"\n";
					int_in2++;
				}
    			delete[] columns_width;
    			delete[] row_present;
			} else if(int_temp == -2){
				cout<<"Info: BOOK don't have "<<database.via<<" member.\n";
			} else	cout<<"Info: BOOK is empty.\n";
		}
		if((database.source == "REPAIR")|(database.source == "ALL")){
			int_temp = r.index;
			if(database.source == "ALL")	cout<<"\n";
			cout<<"REPAIR table contents:\n";
			if(database.second != "-"){
				for(auto column : repair_columns){
					pos = database.via.find(column);
					if(pos == 0) break;
				}
				if(pos != 0) int_temp = -2;
				if((database.last != "-")&(int_temp != -2)){
					if(string_in != "-"){
						
					}	else	check_goto(1, db_q, "Critical error: Unexpected error!");
				}
			}
			if(int_temp > -1) {
				unsigned int * columns_width = new unsigned int [(sizeof(repair_columns)/sizeof(*repair_columns)) - 1];
				int_in = 0;
				for (auto column : repair_columns){
					columns_width[int_in] = column.size() + 2;
					int_in++;
				}
				for (auto r_ : repair) {
        			if(to_string(r_.index).size() > columns_width[0]){
        				columns_width[0] = to_string(r_.index).size() + 2;
					}
					if(r_.type.size() > columns_width[1]){
        				columns_width[1] = r_.type.size() + 2;
					}
					if(r_.info.size() > columns_width[2]){
        				columns_width[2] = r_.info.size() + 2;
					}
					if(r_.objections.size() > columns_width[3]){
        				columns_width[3] = r_.objections.size() + 2;
					}
					if(to_string(r_.days).size() > columns_width[4]){
        				columns_width[4] = to_string(r_.days).size() + 2;
					}
    			}
    			int_in = 0;
    			for (auto col : repair_columns){
    				cout<<col;
    				for(int i = 0; i <= columns_width[int_in] - repair_columns[int_in].size(); i++){
    					cout<<" ";
					}
					int_in++;
				}
				cout<<"\n";
    			for (auto r_ : repair){
    				cout<<r_.index;
    				for(int i = 0; i <= columns_width[0] - to_string(r_.index).size(); i++){
    					cout<<" ";
					}
					cout<<r_.type;
    				for(int i = 0; i <= columns_width[1] - r_.type.size(); i++){
    					cout<<" ";
					}
					cout<<r_.info;
    				for(int i = 0; i <= columns_width[2] - r_.info.size(); i++){
    					cout<<" ";
					}
					cout<<r_.objections;
    				for(int i = 0; i <= columns_width[3] - r_.objections.size(); i++){
    					cout<<" ";
					}
					cout<<r_.days;
    				for(int i = 0; i <= columns_width[4] - to_string(r_.days).size(); i++){
    					cout<<" ";
					}
					cout<<fixed<<setprecision(2)<<r_.cost<<"\n";
				}
    			delete[] columns_width;
			} else if(int_temp == -2){
				cout<<"Info: REPAIR don't have "<<database.via<<" member.\n";
			} else	cout<<"Info: REPAIR is empty.\n";
		}
		if((database.source == "HOME")|(database.source == "ALL")){
			int_temp = h.index;
			if(database.source == "ALL")	cout<<"\n";
			cout<<"HOME table contents:\n";
			if(database.second != "-"){
				for(auto column : home_columns){
					pos = database.via.find(column);
					if(pos == 0) break;
				}
				if(pos != 0) int_temp = -2;
				if((database.last != "-")&(int_temp != -2)){
					if(string_in != "-"){
						
					}	else	check_goto(1, db_q, "Critical error: Unexpected error!");	
				}
			}
			if(int_temp > -1) {
				unsigned int * columns_width = new unsigned int [(sizeof(home_columns)/sizeof(*home_columns)) - 1];
				int_in = 0;
				for (auto column : home_columns){
					columns_width[int_in] = column.size() + 2;
					int_in++;
				}
				for (auto h_ : home) {
        			if(to_string(h_.index).size() > columns_width[0]){
        				columns_width[0] = to_string(h_.index).size() + 2;
					}
					if(h_.object_name.size() > columns_width[1]){
        				columns_width[1] = h_.object_name.size() + 2;
					}
					if(h_.description.size() > columns_width[2]){
        				columns_width[2] = h_.description.size() + 2;
					}
					if(to_string(h_.days_2buy).size() > columns_width[3]){
        				columns_width[3] = to_string(h_.days_2buy).size() + 2;
					}
    			}
    			int_in = 0;
    			for (auto col : home_columns){
    				cout<<col;
    				for(int i = 0; i <= columns_width[int_in] - home_columns[int_in].size(); i++){
    					cout<<" ";
					}
					int_in++;
				}
				cout<<"\n";
    			for (auto h_ : home){
    				cout<<h_.index;
    				for(int i = 0; i <= columns_width[0] - to_string(h_.index).size(); i++){
    					cout<<" ";
					}
					cout<<h_.object_name;
    				for(int i = 0; i <= columns_width[1] - h_.object_name.size(); i++){
    					cout<<" ";
					}
					cout<<h_.description;
    				for(int i = 0; i <= columns_width[2] - h_.description.size(); i++){
    					cout<<" ";
					}
					cout<<h_.days_2buy;
    				for(int i = 0; i <= columns_width[3] - to_string(h_.days_2buy).size(); i++){
    					cout<<" ";
					}
					cout<<fixed<<setprecision(2)<<h_.price<<"\n";
				}
    			delete[] columns_width;
			} else if(int_temp == -2){
				cout<<"Info: HOME don't have "<<database.via<<" member.\n";
			} else	cout<<"Info: HOME is empty.\n";
		}
		goto db_q;
	} else {
		//Boiiii what just you did?!
		cout<<"\nInput error: No operations linked with "<<string_in<<"\n";
		goto idx_txt;
	}
	goto idx_txt;
	return 0;
}
