#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Labirint
{
    public:

    int N; //размер лабиринта
    int** lab_int; //двумерный массив int, аналог массива char
    //где следующие обозначения: '.' -> 0; '_' -> 1; 'x' -> 2
    char** lab; //двумерный массив - карта лабиринта
    char** lab_copy; //копия лабиринта
    vector<int> start; //вектор с координатами старта
    vector<int> finish;//вектор с координатами финиша
    vector<string> commands;//вектор с набором команд

    /*Labirint(int N_input){
    	//конструктор
        N = N_input;

        lab = new char*[N];
        for(int i = 0; i < N; i++)
        {
            lab[i] = new char[N];
        }
    }*/

    void read_from_file(){
    	//функция считывания карты лабиринта из файла
    	char c;
    	ifstream file("labir.txt");
    	file >> N;
    	file.ignore(1);
    	lab = new char*[N];
    	lab_copy = new char*[N];
    	lab_int = new int*[N];
    	for(int i = 0; i < N; i++){
    		lab[i] = new char[N];
    		lab_copy[i] = new char[N];
    		lab_int[i] = new int[N];
    	}
    	for(int i = 0; i < N; i++){
    		for(int j = 0; j < N; j++){
    			file >> c;
    			if(c != ' '){
    				lab[i][j] = c;
    				lab_copy[i][j] = c;
    				if(c == '.'){
    				    lab_int[i][j] = 0;
    				}
    				if(c == '_'){
    					lab_int[i][j] = 1;
    				}
    				if(c == 'x' || c == 'X'){
    				    lab_int[i][j] = 2;
    				}
    			}
    		}
    	}
    }

    /*void Read(){
    	//функция ввода карты лабиринта с консоли
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cin >> lab[i][j];
            }
        }
    }*/

    void find_start(){
    	//будем искать координаты старта и запишем их в вектор
    	for(int i = 0; i < N; i++){
    		for(int j = 0; j < N; j++){
    			if(lab[i][j] == 'x' || lab[i][j] == 'X'){
    				start.push_back(i);
    				start.push_back(j);
    				break;
    			}
    		}
    	}
    }

    void find_finish(){
    	//будем искать финиш обходом по краям поля, потому что по условию корридор
    	//заканчивается на границе карты

    	//ищем финиш по вертикалям
    	for(int i = 0; i < N; i++){
    		if(lab[i][0] == '.'){
    			finish.push_back(i);
    			finish.push_back(0);
    			break;
    		}
    		if(lab[i][N - 1] == '.'){
    		    finish.push_back(i);
    		    finish.push_back(N - 1);
    		    break;
    		}
    	}
    	//ищем финиш по горизонталям
    	for(int j = 0; j < N; j++){
    	    if(lab[0][j] == '.'){
    	    	finish.push_back(0);
    	    	finish.push_back(j);
    	    	break;
    	    }
    	    if(lab[N - 1][j] == '.'){
    	    	finish.push_back(N - 1);
    	    	finish.push_back(j);
    	    	break;
    	    }
    	}
    }

    void print_start_finish(){
    	//функция печатает координаты старта и финиша
    	cout << "start is ";
    	for(auto i : start){
    		cout << i << " ";
    	}
    	cout << endl << "finish is ";
    	for(auto i : finish){
    	    cout << i << " ";
    	}
    	cout << endl;
    }

    void Print(){
    	//вывод карты лабиринта в консоль
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cout << setw(4) << lab_int[i][j];
            }
            cout << endl;
        }
    }

    vector<string> find_direction(int i, int j){
    	//ищет возможные варианты направлений в зависимости от места,
    	//где находится в данный момент

    	//в функцию подаем координаты данного места, где находимся сейчас

    	vector<string> direction;//вектор, в который запишутся доступные для движения направления

    	//если сверху 0, то там свободно и можно идти
    	if(lab_int[i - 1][j] == 0) direction.push_back("up");
    	//если снизу 0, то там свободно и можно идти
    	if(lab_int[i + 1][j] == 0) direction.push_back("down");
    	//аналогично
    	if(lab_int[i][j - 1] == 0) direction.push_back("left");
    	if(lab_int[i][j + 1] == 0) direction.push_back("right");

    	//возвращаем вектор, содержащий допустимые направления движения
    	return direction;
    }



    void volna_change_lab_int(int& i, int& j,const vector<string>& direction){
    	//функция изменяющая наш int-овый двумерный массив по мере движения

    	//в нее подается 2 координаты и вектор допустимых направлений движений. Смотрим
    	//в векторе, какие направления движения нам доступны и делаем шаг

    	//шаг - так как мы реализовываем волновой алгоритм, то под шагом подразумевается
    	//найти все окружающие нас непомеченные ячейки и пометить их значением k + 1,
    	//где k - это значение данной ячейки, в которой мы находимся в данный момент

    	//я сделал 4 пары координат для каждого варианта направления движения, чтобы не было путаницы
    	//возможно это не самый рациональный и практичный ход, но именно так код работает
    	//я пробовал по разному и, скажу честно, есть вариант не использовать 8 переменных, но
    	//тогда можно немного запутаться. Суть заключается в том, что в каждом условном операторе можно
    	//после присвоения ячейки нужного значения, делать "откат" координаты, но это смотрится
    	//немного странно. То есть если для направления "up" мы уменьшаем координату i на единицу,
    	//то после присваивания lab_int[i][j] = k + 1; можно сделать откат i++; Если такой вариант вас
    	//устроит, то можно сделать так, но для более эффективного понимания сути работы функции
    	//сначала лучше понять на примере 8 независимых друг от друга координат
    	int i1 = i;
    	int j1 = j;
    	int i2 = i;
    	int j2 = j;
    	int i3 = i;
    	int j3 = j;
    	int i4 = i;
    	int j4 = j;
    	//если доступно движение вверх, то уменьшаем координату i1 на единицу и присваиваем
    	//этой ячейке следующее значение (на единицу больше текущего)
    	if(find(direction.begin(), direction.end(), "up") != direction.end()){
    		int k = lab_int[i][j];
    		i1--;
    		lab_int[i1][j1] = k + 1;
    	}
    	//аналогично делаем для направлений вниз, направо и влево
    	if(find(direction.begin(), direction.end(), "down") != direction.end()){
    	    int k = lab_int[i][j];
    	    i2++;
    	    lab_int[i2][j2] = k + 1;
    	}
    	if(find(direction.begin(), direction.end(), "left") != direction.end()){
    	    int k = lab_int[i][j];
    	    j3--;
    	    lab_int[i3][j3] = k + 1;
    	}
    	if(find(direction.begin(), direction.end(), "right") != direction.end()){
    	    int k = lab_int[i][j];
    	    j4++;
    	    lab_int[i4][j4] = k + 1;
    	}
    }

    void volna(){
    	//функция распространения волны


    	//берем координаты старта и финиша
    	int i_start = start[0];
    	int j_start = start[1];
    	int i_finish = finish[0];
    	int j_finish = finish[1];
    	//k - это текущее зачение нашей ячейки. Для ячейки старта оно равно 2
    	int k = lab_int[i_start][j_start];

    	//вектор направлений движения
    	vector<string> direction;

    	//пока ячейка финиша = 0 (то есть пока мы до нее не добрались и не изменили)
    	while(lab_int[i_finish][j_finish] == 0){
    		//проходим по каждой ячейке нашего массива
    		for(int i = 0; i < N; i++){
    			for(int j = 0; j < N; j++){
    				//если ячейка равна текущему значению и не равна 1 (1 это препятствие)
    				if(lab_int[i][j] == k && lab_int[i][j] != 1){
    					//то находим возможные направления движения из этой ячейки
    					direction = find_direction(i, j);
    					//меняем значения всех возможных ячеек рядом с ней на значение
    					//больше на 1 чем текущее
    					volna_change_lab_int(i, j, direction);
    				}
    			}
    		}
    		//пройдясь по всем ячейкам и изменив все возможные, делаем текущее значение ячейки на 1 больше
    		k++;
    	}
    }

    char min_way(int i, int j){
    	//функция нахождения минимального пути.

    	//или, если точнее, нахождение минимального значения ячейки из всех ячеек,
    	//окружающих текущую ячейку, координаты которой мы подали в функцию

    	//на мой взгляд это самая сложная для понимания функция (или правильнее метод класса) программы

    	//словарь в котором будут содержаться пары: значение ячейки - 'направление движение в качестве символа'
    	//направление движение как символы я обозначил как u, d, r и l, где u - up; d - down; r - right; l - left
    	map<int, char> m;
    	//переменная минимального значения
    	int min;
    	//вектор, в который я запихну отдельно значения всех окружающих ячеек
    	vector<int> value;
    	//если снизу значение ячейки меньше, чем данное и оно не равно 0 или 1, то
    	if((lab_int[i + 1][j] != 1 && lab_int[i + 1][j] < lab_int[i][j])
    			&& lab_int[i + 1][j] != 0){
    		//кладем значение ячейки и элемент - 'вниз', в словарь
    	    m[lab_int[i + 1][j]] = 'd';
    	    //пихаем в вектор значение ячейки
    	    value.push_back(lab_int[i + 1][j]);
    	}
    	//аналогично для направлений u, r и l
    	if((lab_int[i - 1][j] != 1 && lab_int[i - 1][j] < lab_int[i][j])
    			&& lab_int[i - 1][j] != 0){
    	    m[lab_int[i - 1][j]] = 'u';
    	    value.push_back(lab_int[i - 1][j]);
    	}
    	if((lab_int[i][j + 1] != 1 && lab_int[i][j + 1] < lab_int[i][j])
    			&& lab_int[i][j + 1] != 0){
    	    m[lab_int[i][j + 1]] = 'r';
    	    value.push_back(lab_int[i][j + 1]);
    	}
    	if((lab_int[i][j - 1] != 1 && lab_int[i][j - 1] < lab_int[i][j])
    			&& lab_int[i][j - 1] != 0){
    	    m[lab_int[i][j - 1]] = 'l';
    	    value.push_back(lab_int[i][j - 1]);
    	}
    	//сделаем сортировку вектора
    	sort(value.begin(), value.end());
    	//тогда минимальное значение это первое значение в векторе
    	min = value[0];
    	//возвращаем направление наилучшего движения
    	return m[min];
    }

    void find_way(){
    	//функция восстановления пути из точки финиша до точки старта

    	//переменная, в которую будем писать возвращаемое знаечние из функции min_way
    	char c;
    	//координаты старта и финиша (они снова нам нужны :) )
    	int i_start = start[0];
    	int j_start = start[1];
    	int i_finish = finish[0];
    	int j_finish = finish[1];
    	//пока координаты старта не сравняются с координатами финиша
    	while(i_start != i_finish || j_start != j_finish){
    		//начинаем с точки финиша
    		//кладем в с значение от функции min_way
    		c = min_way(i_finish, j_finish);
    		//пометили текущее местоположение как 0
    		lab_int[i_finish][j_finish] = 0;
    		//в зависимости от с делаем шаг в нужную сторону
    		//изменяем координату финиша
    		if(c == 'd') i_finish++;
    		if(c == 'u') i_finish--;
    		if(c == 'r') j_finish++;
    		if(c == 'l') j_finish--;
    		//так делаем пока координаты финиша не будут равны стартовым
    	}
    }

    string find_way_command(int i, int j){
    	//функция возвращающая команды куда нужно идти от текущего местоположения

    	//да, сначала кажется, что подобная функция уже была и я повторяю код, но нет
    	//эта функция дает команды уже для полностью найденного короткого пути, который полностью
    	//помечен 0, то есть это тот самый нужный нам путь и он единственный (нет уже больше тупиков,
    	//ветвлений, петель итд

    	//а похожая выше функция формировала вектор из возможных вариантов движений.
    	//в принципе ее можно было бы использовать, но нужно было бы считывать значение с вектора
    	//что могло бы запутать вас. Сейчас, когда я полностью знаю свой код, осознаю, что он делает
    	//я могу так рассуждать, но когда я его только только писал, то сделать лишний метод в классе
    	//но лишь бы не запутаться для было приоритетом. Я уверен, вам будет с самого начала понять
    	//программу с этой функцией, чем без нее :)
    	if(lab_int[i - 1][j] == 0) return "up";
    	if(lab_int[i + 1][j] == 0) return "down";
    	if(lab_int[i][j + 1] == 0) return "right";
    	return "left";
    }

    void command(){
    	//метод поиска пути

    	//координаты старта и финиша (опять!!)
    	int i_start = start[0];
    	int j_start = start[1];
    	int i_finish = finish[0];
    	int j_finish = finish[1];

    	//определяем куда идти. Пока координаты старта не сравняются с координатами финиша
    	//двигаемся по корридору и записываем в вектор команды
    	while(i_start != i_finish || j_start != j_finish){
    		//в строку пишем направление движения
    		string s = find_way_command(i_start, j_start);
    		//если направление движения наверх
    		if(s == "up"){
    			//то в массиве лабиринта присваиваем текущему местоположению 1
    			lab_int[i_start][j_start] = 1;
    			//изменяем координату для дальнейшего движения
    			i_start--;
    			//записываем нужную команду в вектор команд
    			commands.push_back("Наверх!");
    		}
    		//аналогично для других команд
    		else if(s == "down"){
    		    lab_int[i_start][j_start] = 1;
    		    i_start++;
    		    commands.push_back("Вниз!");
    		}
    		else if(s == "left"){
    		    lab_int[i_start][j_start] = 1;
    		    j_start--;
    		    commands.push_back("Налево!");
    		}
    		else if(s == "right"){
    		    lab_int[i_start][j_start] = 1;
    		    j_start++;
    		    commands.push_back("Направо!");
    		}
    	}
    }

    //просто метод, возвращающий вектор команд
    vector<string> return_func(){
    	return commands;
    }

    //тут очевидно
    void print_commands(){
    	//печатает команды из вектора команд
    	for(auto i : commands){
    		cout << i << endl;
    	}
    }
};

bool IfFileExists (const string& name)
{
    ifstream f(name.c_str());
    return f.good();
}

int main()
{
	//вектор ответов - где будут лежать все команды
	vector<string> answers;

	//русские буквы в консоли
	setlocale(LC_ALL, "Russian");

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

    Labirint MyLab;
    MyLab.read_from_file();
    MyLab.find_start();
    MyLab.find_finish();
    //MyLab.Print();
    //cout << endl;
    MyLab.volna();
    MyLab.find_way();
    //MyLab.Print();
    MyLab.command();
    MyLab.print_commands();
    answers = MyLab.return_func();
    for(auto i : answers){
    	fout << i << endl;
    }
    return 0;
}
