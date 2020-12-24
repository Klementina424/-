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
		std::cout << "������� �����:" << std::endl
			<< ' ' << (readType == 0 ? '>' : ' ') << " � ������� " << (readType == 0 ? '<' : ' ') << std::endl
			<< ' ' << (readType == 1 ? '>' : ' ') << " �� ����� test.txt " << (readType == 1 ? '<' : ' ') << std::endl << std::endl
			<< "��� ����������� ����� �������� ���� �������������� ���������" << std::endl
			<< "��� ������ ������ ���� ������� Enter" << std::endl
			<< "��� ���������� ������ ���������� ������� Esc";

		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			if (ch == Up || ch == Down)
				readType = (readType == 0 ? 1 : 0);
		}

		if (ch == Enter) {
			system("cls");
			while (ch != Esc) {
				std::cout << "������� ����������� �������� ������" << std::endl
					<< ' ' << (writeType == 0 ? '>' : ' ') << " �� ������� " << (writeType == 0 ? '<' : ' ') << std::endl
					<< ' ' << (writeType == 1 ? '>' : ' ') << " � ����� answer.txt " << (writeType == 1 ? '<' : ' ') << std::endl << std::endl
					<< "��� ����������� ����� �������� ���� �������������� ���������" << std::endl
					<< "��� ������ ������ ���� ������� Enter" << std::endl
					<< "��� ���������� ������ ���������� ������� Esc";

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
						cout << "������� �������������� ���������, ��������� �� ����� � �������������� ������:" << endl;
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
							cout << "���������� ������ ���������� ���������: " << Test.print_prefix() << endl;
							cout << "��������� ����������: " << Test.get_result() << endl;
						}
						catch (const char* error)
						{
							cout << error << endl;
						}
					}
					else {
						ofstream out("answer.txt");
						try {
							out << "���������� ������ ���������� ���������: " << Test.print_prefix() << endl;
							out << "��������� ����������: " << Test.get_result() << endl;
						}
						catch (const char* error)
						{
							out << error << endl;
						}
						out.close();
					}

					std::cout << "��� ���������� ������ ��������� ������� ����� �������";
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
