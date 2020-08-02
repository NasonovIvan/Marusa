#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//функция ответа по заданной команде и полю
string answer(string& command, vector<string>& board){
	int ia = 0;
	int i1 = 0;
	char Ca, C1;
	Ca = command[0];
	C1 = command[1];
	while (Ca != board[ia][0]){
		//cout << "Ca for ia = " << i << " is " << Ca << endl;
		ia++;
	}
	while (C1 != board[0][i1]){
		//cout << "Ca for ia = " << i << " is " << Ca << endl;
		i1++;
	}
	if (board[ia][i1] == 'x'){
		return "Попал!";
	}
	return "Промах!";
}

//функция считывания комманд
vector<string> read_commands(){
	string s;
	vector<string> v;
	for(int i = 0; i < 10; i++){
		cin >> s;
		v.push_back(s);
	}
	return v;
}

//функция считывания поля
vector<string> read_board(){
	//считывает доску с консоли
	vector<string> board;
	string s;
	for (int i = 0; i < 10; i++){
		getline(cin, s);
		board.push_back(s);
	}
	return board;
}

/*void PrintVec(vector<string>& v){
	for(auto i : v){
		cout << i << "\n";
	}
}*/

/* Функция проверки, существует ли файл */
bool IfFileExists (const string& name)
{
    ifstream f(name.c_str());
    return f.good();
}

int main(){
	// Номер файла
	int file_number;

	// Бежим по номерам файла 0, 1, 2 ...
	for(file_number = 0; ; file_number++){
		// Если очередной файл не существует -- выходим из цикла
		if(!IfFileExists("file" + to_string(file_number) + ".txt")){
			break;
		}
	}

	//открываем файл
	ofstream fout("file" + to_string(file_number) + ".txt");

	vector<string> board;
	vector<string> commands;
	vector<string> answers;

	board = read_board();
	commands = read_commands();
	//PrintVec(board);
	for(int i = 0; i < 10; i++){
		string command = commands[i];
		string s = answer(command, board);
		answers.push_back(s);
	}
	for(int i = 0; i < 10; i++){
		cout << answers[i] << "\n";
		fout << answers[i] << "\n";
	}
	return 0;
}
