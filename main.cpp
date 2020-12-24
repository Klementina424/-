#include <iostream>
#include <string>
#include "calculator.h"
#include <conio.h>
#include <fstream>


using namespace std;

constexpr unsigned char Enter = 13, Esc = 27, Up = 72, Down = 80;

int main()
{
	setlocale(LC_ALL, "Rus");

	unsigned char readType = 0, writeType = 0, ch = 0;
	while (ch != Esc) {
		std::cout << "Считать ребра:" << std::endl
			<< ' ' << (readType == 0 ? '>' : ' ') << " с консоли " << (readType == 0 ? '<' : ' ') << std::endl
			<< ' ' << (readType == 1 ? '>' : ' ') << " из файла test.txt " << (readType == 1 ? '<' : ' ') << std::endl << std::endl
			<< "Для перемещения между пунктами меню воспользуйтесь стрелками" << std::endl
			<< "Для выбора пункта меню нажмите Enter" << std::endl
			<< "Для завершения работы программмы нажмите Esc";

		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			if (ch == Up || ch == Down)
				readType = (readType == 0 ? 1 : 0);
		}

		if (ch == Enter) {
			system("cls");
			while (ch != Esc) {
				std::cout << "Вывести минимальное остовное дерево" << std::endl
					<< ' ' << (writeType == 0 ? '>' : ' ') << " на консоли " << (writeType == 0 ? '<' : ' ') << std::endl
					<< ' ' << (writeType == 1 ? '>' : ' ') << " в файла answer.txt " << (writeType == 1 ? '<' : ' ') << std::endl << std::endl
					<< "Для перемещения между пунктами меню воспользуйтесь стрелками" << std::endl
					<< "Для выбора пункта меню нажмите Enter" << std::endl
					<< "Для завершения работы программмы нажмите Esc";

				ch = _getch();
				if (ch == 224) {
					ch = _getch();
					if (ch == Up || ch == Down)
						writeType = (writeType == 0 ? 1 : 0);
				}

				if (ch == Enter) {
					system("cls");

					calculator  Test;
					string buf;

					if (readType == 0) {
						cout << "Введите математическое выражение, состоящее из чисел и арифметических знаков:" << endl;
						getline(cin, buf);
					}
					else {
						ifstream in("test.txt");
						getline(in, buf);
						in.close();
					}

					Test.make_prefix(buf);

					if (writeType == 0) {
						try {
							cout << "Префиксная запись введенного выражения: " << Test.print_prefix() << endl;
							cout << "Результат вычисления: " << Test.get_result() << endl;
						}
						catch (const char* error)
						{
							cout << error << endl;
						}
					}
					else {
						ofstream out("answer.txt");
						try {
							out << "Префиксная запись введенного выражения: " << Test.print_prefix() << endl;
							out << "Результат вычисления: " << Test.get_result() << endl;
						}
						catch (const char* error)
						{
							out << error << endl;
						}
						out.close();
					}

					std::cout << "Для завершения работы программы нажмите любую клавишу";
					_getch();
					ch = Esc;
				}

				system("cls");
			}

		}

		system("cls");
	}

	return 0;
}
