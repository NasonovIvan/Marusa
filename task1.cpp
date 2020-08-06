#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class Krestik{
public:

	int N; //размер поля
	char** board; //двумерный массив char, в котором будет поле

	Krestik(int N_input){
		//конструктор
		N = N_input;
		board = new char*[N];
		for(int i = 0; i < N; i++){
			board[i] = new char[N];
		}
	}

	void Read(){
		//метод ввода поля с консоли
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				cin >> board[i][j];
			}
		}
	}

	string check_board_2(){
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



	string check_func(){
	  //определяет победителя
		string s;
		if(check_goriz() != "xO"){
			s = check_goriz();
			return s;
		}
		if(check_vert() != "xO"){
			s = check_vert();
			return s;
		}
		if(check_diag_1() != "xO"){
			s = check_diag_1();
			return s;
		}
		if(check_diag_2() != "xO"){
			s = check_diag_2();
			return s;
			}
		return "xO";
	}

	string check_func_n(){
	  //определяет победителя
		string s;
		if(check_goriz_n() != "xO"){
			s = check_goriz_n();
			return s;
		}
		if(check_vert_n() != "xO"){
			s = check_vert_n();
			return s;
		}
		if(check_diag_1_n() != "xO"){
			s = check_diag_1_n();
			return s;
		}
		if(check_diag_2_n() != "xO"){
			s = check_diag_2_n();
			return s;
			}
		return "xO";
	}

private:
	string check_goriz(){
		//проверка по горизонталям

		//цикл по строкам во всем большом квадрате
		for(int i = 0; i < N; i++){
			//цикл по 3 элементам в строке (горизонталь)
			//выясняем, равны ли 3 элемента подряд в строке
			//(n - 2) потому что идем квадратом по 3
			for(int j = 0; j < (N - 2); j++){
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

	string check_vert(){
		//проверка по вертикалям

		//цикл по элементам во всем большом квадрате
		for(int j = 0; j < N; j++){
			//цикл по строкам в вертикали
			//выясняем, равны ли 3 элемента подряд в столбце
			//(n - 2) потому что идем квадратом по 3
			for(int i = 0; i < (N - 2); i++){
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

	string check_diag_1(){
		//проверка 1 диагонали по всем подквадратам 3 на 3

		//цикл по строкам во всем большом квадрате
		for(int i = 0; i < (N - 2); i++){
			//цикл по 3 элементам в диагонале
			//выясняем, равны ли 3 элемента подряд в диагонале
			//(n - 2) потому что идем квадратом по 3
			for(int j = 0; j < (N - 2); j++){
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

	string check_diag_2(){
		//проверка 2 диагонали по всем подквадратам 3 на 3

		//цикл по строкам во всем большом квадрате
		for(int i = 0; i < (N - 2); i++){
			//цикл по 3 элементам в диагонале
			//выясняем, равны ли 3 элемента подряд в диагонале
			//(n - 2) потому что идем квадратом по 3
			for(int j = 0; j < (N - 2); j++){
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

	string check_vert_n(){
		//проверка полных вертикалей в квадратах больше, чем 3 на 3

		//переменная в которую запишем символ победителя
		char c;
		//вектор символов победителей
		vector<char> winner;

		for(int j = 0; j < N; j++){
		//цикл по i проходим до N - 1 потому что по сути уже заглядываем всегда вперед на 1 символ
			for(int i = 0; i < (N - 1); i++){
				if(board[i][j] == board[i + 1][j] && board[i][j] != '.'){
					c = board[i][j];
				}
				else{
					//'u'просто рандомный символ. Он означает, что в диагонале нет непрерывной последовательности
					//одинаковых символов
					c = 'u';
					break;
				}
			}
			if(c != 'u') winner.push_back(c);
		}
		if(winner.size() == 1){
			if(winner[0] == 'x') return "x";
			else return "O";
		}
		return "xO";
	}

	string check_goriz_n(){
		//проверка полных горизонталей в квадратах больше, чем 3 на 3

		//переменная в которую запишем символ победителя
		char c;
		//вектор символов победителей
		vector<char> winner;

		for(int i = 0; i < N; i++){
		//цикл по j проходим до N - 1 потому что по сути уже заглядываем всегда вперед на 1 символ
			for(int j = 0; j < (N - 1); j++){
				if(board[i][j] == board[i][j + 1] && board[i][j] != '.'){
					c = board[i][j];
				}
				else{
					//'u'просто рандомный символ. Он означает, что в диагонале нет непрерывной последовательности
					//одинаковых символов
					c = 'u';
					break;
				}
			}
			if(c != 'u') winner.push_back(c);
		}
		if(winner.size() == 1){
			if(winner[0] == 'x') return "x";
			else return "O";
		}
		return "xO";
	}



	string check_diag_1_n(){
		//функция проверяющая главную диагональ на одинаковые символы (во всей диагонали)

		//переменная в которую запишем символ победителя
		char c;
		//счетчики
		int i = 0;
		int j = 0;

		//проходим до N - 1 потому что по диагонали заглядываем всегда вперед на 1 элемент
		while(i < (N - 1) && j < (N - 1)){
			if(board[i][j] == board[i + 1][j + 1] && board[i][j] != '.'){
				c = board[i][j];
			}
			else{
				//'u'просто рандомный символ. Он означает, что в диагонале нет непрерывной последовательности
				//одинаковых символов
				c = 'u';
				break;
			}
			i++;
			j++;
		}
		if(c != 'u'){
			if(c == 'x') return "x";
			else return "O";
		}
		return "xO";
	}

	string check_diag_2_n(){
		//функция проверяющая побочную диагональ на одинаковые символы (во всей диагонали)

		//переменная в которую запишем символ победителя
		char c;
		//счетчики
		int i = 0;
		int j = N - 1;

		//проходим до N - 1 потому что по диагонали заглядываем всегда вперед на 1 элемент
		//j > 0 потому что начинаем с правого верхнего края таблички
		while(i < (N - 1) && j > 1){
			if(board[i][j] == board[i + 1][j - 1] && board[i][j] != '.'){
				c = board[i][j];
			}
			else{
				c = 'u';
				break;
			}
			i++;
			j--;
		}
		if(c != 'u'){
			if(c == 'x') return "x";
			else return "O";
		}
		return "xO";
	}

};

/* Функция проверки, существует ли файл */
bool IfFileExists (const string& name)
{
    ifstream f(name.c_str());
    return f.good();
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

	if (N == 0){
		cout << "xO";
		fout << "xO" << endl;
		fout.close();
	}
	if (N == 1){
		cin >> c;
		cout << c;
		fout << c << endl;
		fout.close();
	}
	if (N == 2){
		Krestik Board(N);
		Board.Read();
		string s = Board.check_board_2();
		cout << s << endl;
		fout << s << endl;
		fout.close();
	}
	if (N >= 3 && N <= 30){
		Krestik Board(N);
		Board.Read();
		string s = Board.check_func();

		//Если условие выигрыша на полях >= 3 подразумевает собой построение последовательности
		//одинаковых символов на ПОЛНОЙ вертикале/горизонтале/диагонали, то использовать нужно
		//нижнюю строчку, а строчку string s = Board.check_func(); закомментить, поскольку она
		//работает при условии, что выигрыш происходит при построении последовательности >= 3 одинаковых
		//символов подряд. Более подробно об этом читай в файле README.md в репозитории

		//string s = Board.check_func_n();
		cout << s << endl;
		fout << s << endl;
		fout.close();
	}
	return 0;
}
