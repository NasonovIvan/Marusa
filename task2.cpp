#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

class Sea_fight{
public:
	vector<string> commands; //вектор команд
	char** board; //двумерный массив char, в котором будет поле
	vector<string> answers; //вектор ответов (попал или промах) в зависимости от команды

	/*Sea_fight(){
		//конструктор
		board = new char*[10];
		for(int i = 0; i < 10; i++){
			board[i] = new char[10];
		}
	}*/

    void read_from_file(){
    	//функция считывания поля из файла
    	string s;
    	char c;
    	ifstream file("board.txt");
    	board = new char*[10];
    	for(int i = 0; i < 10; i++){
    		board[i] = new char[10];
    	}
    	//читаем поле 10 на 10
    	for(int i = 0; i < 10; i++){
    		for(int j = 0; j < 10; j++){
    			file >> c;
    			if(c != ' '){
    				board[i][j] = c;
    			}
    		}
    	}
    	//читаем 10 команд и пихаем их в вектор команд
    	for(int i = 0; i < 10; i++){
    		file >> s;
    		commands.push_back(s);
    	}
    }

	/*void Read(){
		//метод ввода поля с консоли
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 10; j++){
				cin >> board[i][j];
			}
		}
	}*/

    void Print(){
    	//вывод карты лабиринта в консоль
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        //вывод вектора команд в консоль
        for(auto i : commands){
        	cout << i << endl;
        }
    }

    //функция ответа по заданной команде и полю
    void answer(){
    	for(auto command : commands){
    		int ia = 0;
    		int i1 = 0;
    		char Ca, C1;
    		Ca = command[0];
    		C1 = command[1];
    		while (Ca != board[ia][0]){
    			ia++;
    		}
    		while (C1 != board[0][i1]){
    			i1++;
    		}
    		if (board[ia][i1] == 'x' || board[ia][i1] == 'X'){
    			answers.push_back("Попал!");
    		}
    		else answers.push_back("Промах!");
    	}
    }

    vector<string> return_answers(){
    	//функция возвращает вектор ответов
    	return answers;
    }

};

/* Функция проверки, существует ли файл */
bool IfFileExists (const string& name)
{
    ifstream f(name.c_str());
    return f.good();
}

int main(){

	//русские буквы в консоли
	setlocale(LC_ALL, "Russian");
	//вектор ответов
	vector<string> answers;
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

	Sea_fight Fight;
	Fight.read_from_file();
	//Fight.Print();
	Fight.answer();
	answers = Fight.return_answers();
	for(auto answer : answers){
		cout << answer << endl;
		fout << answer << endl;
	}
	fout.close();
	return 0;
}
