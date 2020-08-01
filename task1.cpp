#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

string check_board_2(const vector<string>& board){
	//функция, проверяющая доску 2 на 2
	char c;
	if (board[0][0] == board[0][1] && board[0][0] != '.'){
		c = board[0][0];
		if (c == 'x') return "x";
		return "O";
	}
	if (board[1][0] == board[1][1] && board[1][0] != '.'){
		c = board[1][0];
		if (c == 'x') return "x";
		return "O";
	}
	if (board[0][0] == board[1][0] && board[0][0] != '.'){
		c = board[0][0];
		if (c == 'x') return "x";
		return "O";
	}
	if (board[0][1] == board[1][1] && board[0][1] != '.'){
		c = board[0][1];
		if (c == 'x') return "x";
		return "O";
	}
	if (board[0][0] == board[1][1] && board[0][0] != '.'){
		c = board[0][0];
		if (c == 'x') return "x";
		return "O";
	}
	if (board[0][1] == board[1][0] && board[0][1] != '.'){
		c = board[0][1];
		if (c == 'x') return "x";
		return "O";
	}
	return "xO";
}

string check_goriz(const vector<string>& board){
	//проверка по горизонталям
	int n = board.size();
	//цикл по строкам во всем большом квадрате
	for(int i = 0; i < n; i++){
		//цикл по 3 элементам в строке (горизонталь)
		//выясняем, равны ли 3 элемента подряд в строке
		//(n - 2) потому что идем квадратом по 3
		for(int j = 0; j < (n - 2); j++){
			if(board[i][j] == board[i][j + 1] &&
			board[i][j + 1] == board[i][j + 2] && board[i][j] != '.' &&
			board[i][j + 1] != '.' && board[i][j + 2] != '.'){
			char winner = board[i][j];
			if (winner == 'x') return "x";
			return "O";
			}
		}
	}
	return "xO";
}

string check_vert(const vector<string>& board){
	//проверка по вертикалям
	int n = board.size();
	//цикл по элементам во всем большом квадрате
	for(int j = 0; j < n; j++){
		//цикл по строкам в вертикали
		//выясняем, равны ли 3 элемента подряд в столбце
		//(n - 2) потому что идем квадратом по 3
		for(int i = 0; i < (n - 2); i++){
			if(board[i][j] == board[i + 1][j] &&
			board[i + 1][j] == board[i + 2][j] && board[i][j] != '.' &&
			board[i + 1][j] != '.' && board[i + 2][j] != '.'){
			char winner = board[i][j];
			if (winner == 'x') return "x";
			return "O";
			}
		}
	}
	return "xO";
}

string check_diag_1(const vector<string>& board){
	//проверка 1 диагонали по всем подквадратам 3 на 3
	int n = board.size();
	//цикл по строкам во всем большом квадрате
	for(int i = 0; i < (n - 2); i++){
		//цикл по 3 элементам в диагонале
		//выясняем, равны ли 3 элемента подряд в диагонале
		//(n - 2) потому что идем квадратом по 3
		for(int j = 0; j < (n - 2); j++){
			if(board[i][j] == board[i + 1][j + 1] &&
			board[i + 1][j + 1] == board[i + 2][j + 2] && board[i][j] != '.' &&
			board[i + 1][j + 1] != '.' && board[i + 2][j + 2] != '.'){
			char winner = board[i][j];
			if (winner == 'x') return "x";
			return "O";
			}
		}
	}
	return "xO";
}

string check_diag_2(const vector<string>& board){
	//проверка 2 диагонали по всем подквадратам 3 на 3
	int n = board.size();
	//цикл по строкам во всем большом квадрате
	for(int i = 0; i < (n - 2); i++){
		//цикл по 3 элементам в диагонале
		//выясняем, равны ли 3 элемента подряд в диагонале
		//(n - 2) потому что идем квадратом по 3
		for(int j = 0; j < (n - 2); j++){
			if(board[i][j + 2] == board[i + 1][j + 1] &&
			board[i + 1][j + 1] == board[i + 2][j] && board[i][j + 2] != '.' &&
			board[i + 1][j + 1] != '.' && board[i + 2][j] != '.'){
			char winner = board[i][j + 2];
			if (winner == 'x') return "x";
			return "O";
			}
		}
	}
	return "xO";
}

string check_func(const vector<string>& board){
  //определяет победителя
	string s;
	if(check_goriz(board) != "xO"){
		s = check_goriz(board);
		return s;
	}
	if(check_vert(board) != "xO"){
		s = check_vert(board);
		return s;
	}
	if(check_diag_1(board) != "xO"){
		s = check_diag_1(board);
		return s;
	}
	if(check_diag_2(board) != "xO"){
		s = check_diag_2(board);
		return s;
		}
	return "xO";
}

/*void PrintVec(vector<string>& v){
	//печатает доску
	int n = v.size();
	//cout << "n = " << n << endl;
	//cout << "s = " << s << endl;
	for (int i = 0; i < n; i++){
		cout << v[i] << "\n";
	}
}*/

/* Функция проверки, существует ли файл */
bool IfFileExists (const string& name)
{
    ifstream f(name.c_str());
    return f.good();
}

vector<string> read_board(int n){
	//считывает доску с консоли
	vector<string> board;
	string s;
	for (int i = 0; i < n; i++){
		cin >> s;
		board.push_back(s);
	}
	return board;
}

int main(){
	int N;
	char c;

	// Номер файла
	int file_number;

	// Бежим по номерам файла 0, 1, 2 ...
	for(file_number = 0; ; file_number++)
	{
		// Если очередной файл не существует -- выходим из цикла
		if(!IfFileExists("file" + to_string(file_number) + ".txt"))
		{
			break;
	    }
	}

	//открываем файл
	ofstream fout("file" + to_string(file_number) + ".txt");

	cin >> N;
	if (N == 1){
		cin >> c;
		cout << c;
		fout << c << endl;
		fout.close();
	}
	if (N == 2){
		vector<string> board;
		board = read_board(N);
		string s2 = check_board_2(board);
		cout << s2 << endl;
		fout << s2 << endl;
		fout.close();
	}
	if (N >= 3 && N <= 30){
		vector<string> board;
		board = read_board(N);
		string s3 = check_func(board);
		cout << s3 << endl;
		fout << s3 << endl;
		fout.close();
	}
	return 0;
}
