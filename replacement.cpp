#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace std;
#pragma warning ( disable : 4996 )

#define M 5 //����� �޸� ����

int test_case;
int sort_num;
int s; //�о���� ��

vector<int>buffer; //tast�� �����͸� �о�� ��
vector<int>memory; //������ �����͸� ���� ��
vector<int>freeze; //����� �����͸� ���� ��
vector<int>unfrozen; //���� ������ ���� ����
vector<vector<int>>run_print;

vector<int>F = { 1000, 1000, 1000, 1000, 1000 };

int main(void) {
	ifstream fin;
	fin.open("replacement_input.txt");
	ofstream fout;
	fout.open("replacement_output.txt");

	if (!fin) {
		cerr << "���� ���� ����"; return 0;
	}
	if (!fout) {
		cerr << "���� ���� ����"; return 0;
	}

	fin >> test_case; cout << "test_case " << test_case << endl; //1

	for (int test_case_loop = 0; test_case_loop < test_case; test_case_loop++) {
		int readCnt = 0;
		fin >> sort_num; cout << "sort_num " << sort_num << endl; //2

		for (int i = 0; i < M; i++) {
			fin >> s;
			readCnt++;
			buffer.push_back(s);
		}

		int buffer_loop_count = 1;

		while (buffer != F) { //���ĵɶ����� �ݺ�
			cout << buffer_loop_count << "��°" << endl;
			cout << "���� Ƚ��: " << readCnt << endl;

			//�׽�Ʈ�� ��� 3
			cout << "���ۿ� �� ������: ";
			for (int i = 0; i < M; i++) {
				cout << buffer.at(i) << ' ';
			}
			cout << endl;

			int min;

			min = *min_element(buffer.begin(), buffer.end());
			cout << "�ּҰ�: " << min << endl; //���4
			int minIndex = find(buffer.begin(), buffer.end(), min) - buffer.begin();
			cout << "�ּҰ� �ε���: " << minIndex << endl; //�ּҰ��� �ε��� |���5

			if (buffer_loop_count == 1) {
				memory.push_back(min); //�޸𸮿� ����

				fin >> s; //���ۿ� fin�ϱ�
				readCnt++;
				buffer.erase(buffer.begin() + minIndex); //�ּҰ� ����
				cout << "�ּҰ��� �����߽��ϴ�." << endl;
				buffer.insert(buffer.begin() + minIndex, s); //�ּҰ� �ڸ��� ������ �ֱ�
				cout << "�ּҰ� �ڸ��� [" << s << "]�� �־����ϴ�." << endl;
			}
			else if (min < memory.back()) {
				freeze.push_back(min);
				buffer.at(minIndex) = 1000; //freeze �� �ε����� ���� �����ϱ� ����
				cout << "�ּҰ� �ڸ��� [1000]�� �־����ϴ�." << endl;
			}
			else {
				memory.push_back(min); //�޸𸮿� ����

				buffer.erase(buffer.begin() + minIndex); //�ּҰ� ����
				cout << "�ּҰ��� �����߽��ϴ�." << endl;
				if (readCnt == sort_num) { // �� �о��ٸ�
					buffer.insert(buffer.begin() + minIndex, 1000); //�ּҰ� �ڸ��� 1000�ֱ�
					cout << "�ּҰ� �ڸ��� [" << s << "]�� �־����ϴ�." << endl;
				}
				else { // ���� �� �о��ٸ�
					fin >> s; //���ۿ� fin�ϱ�
					readCnt++;
					buffer.insert(buffer.begin() + minIndex, s); //�ּҰ� �ڸ��� ������ �ֱ�
					cout << "�ּҰ� �ڸ��� [" << s << "]�� �־����ϴ�." << endl;
				}
			}
			cout << "�޸� �� ������: ";
			for (int i = 0; i < memory.size(); i++) {
				cout << memory.at(i) << ' ';
			}
			cout << endl;

			cout << "freeze Ȯ��: ";
			for (int i = 0; i < freeze.size(); i++) {
				cout << freeze.at(i) << ' ';
			}
			cout << endl;

			cout << "���ο� ���� Ȯ�ο�: "; //��� 6
			for (int i = 0; i < buffer.size(); i++) {
				cout << buffer.at(i) << ' ';
			}
			cout << endl << endl;

			buffer_loop_count++;
		}
		run_print.push_back(memory); //run�� memory����
		memory.clear(); //���ο� ������ ���� memory ����
		buffer.clear(); //���� ��� ���� ���


		// ���� �ٽ� ���� ����


		bool read_complete_flag = true;
		//bool buffer_flag = true;
		while (read_complete_flag || !freeze.empty()) {
			//buffer_flag = true;
			for (int i = 0; i < freeze.size(); i++) { //freeze�� �͵� unfrozen���� �ű��
				unfrozen.push_back(freeze.at(i));
			}
			freeze.clear(); //�Ű����ϱ� freeze ���

			cout << "unfrozen.size(): " << unfrozen.size() << endl;

			for (int i = 0; i < unfrozen.size(); i++) {  //unfrozen Ȯ�ο�
				cout << unfrozen.at(i) << ' ';
			}
			cout << endl;

			cout << "------------------------------------���� ����------------------------------------" << endl;

			freeze.clear();

			for (int i = 0; i < run_print.size(); i++) {  //run_print Ȯ�ο�
				for (int j = 0; j < run_print.at(i).size(); j++) {
					cout << run_print.at(i).at(j) << ' ';
				}
				cout << endl;
			}

			//���� �ݺ����̶� ���� (freeze����)
			int freeze_count = 1;
			while (buffer != F) { //freeze ���� �� �ٽ� ����
				cout << freeze_count << "��°" << endl;
				cout << "���� Ƚ��: " << readCnt << endl;
				cout << endl;
				if (freeze_count == 1) {
					if (unfrozen.size() < M) { // 5������ ������ 5�� �� �о���ϱ� ������ŭ �а� ����
						cout << "5���� ���� ��" << endl;
						for (int i = 0; i < M; i++) {
							if (i > (unfrozen.size() - 1)) {
								buffer.push_back(1000);
							}
							else {
								buffer.push_back(unfrozen.at(i));
							}
						}
						cout << endl;
					}
					else { // 5�� �̻��̸� ������ �Ȱ��� ��
						cout << "5���� ��" << endl;
						for (int i = 0; i < M; i++) {
							buffer.push_back(unfrozen.at(i));
						}
					}
					unfrozen.clear();
				}

				cout << "���ۿ� �� ������: ";
				for (int i = 0; i < buffer.size(); i++) {
					cout << buffer.at(i) << ' ';
				}
				cout << endl;

				int min;

				min = *min_element(buffer.begin(), buffer.end());
				cout << "�ּҰ�: " << min << endl; //���4
				int minIndex = find(buffer.begin(), buffer.end(), min) - buffer.begin();
				cout << "�ּҰ� �ε���: " << minIndex << endl; //�ּҰ��� �ε��� |���5

				buffer.erase(buffer.begin() + minIndex); //�ּҰ� ����
				cout << "�ּҰ��� �����߽��ϴ�." << endl;
				if (freeze_count == 1) { //ù��°�϶���
					memory.push_back(min); //�޸𸮿� ����
					if (readCnt == sort_num) { // �� �о��ٸ�
						read_complete_flag = false;
						buffer.insert(buffer.begin() + minIndex, 1000); //�ּҰ� �ڸ��� 1000�ֱ�
						cout << "�ּҰ� �ڸ��� [1000]�� �־����ϴ�." << endl;
					}
					else { // ���� �� �о��ٸ�
						fin >> s; //���ۿ� fin�ϱ�
						readCnt++;
						buffer.insert(buffer.begin() + minIndex, s); //�ּҰ� �ڸ��� ������ �ֱ�
						cout << "�ּҰ� �ڸ��� [" << s << "]�� �־����ϴ�." << endl;
					}
				}
				else if (min < memory.back()) {
					freeze.push_back(min);
					buffer.insert(buffer.begin() + minIndex, 1000); //�ּҰ� �ڸ��� 1000�ֱ�
					//buffer.at(minIndex) = 1000; //freeze �� �ε����� ���� �����ϱ� ����
					cout << "�ּҰ� �ڸ��� [1000]�� �־����ϴ�." << endl;
				}
				else {
					memory.push_back(min); //�޸𸮿� ����
					if (readCnt == sort_num) { // �� �о��ٸ�
						cout << "�� �о����ϴ�." << endl;
						read_complete_flag = false;
						buffer.insert(buffer.begin() + minIndex, 1000); //�ּҰ� �ڸ��� 1000�ֱ�
						cout << "�ּҰ� �ڸ��� [1000]�� �־����ϴ�." << endl;
					}
					else { // ���� �� �о��ٸ�
						fin >> s; //���ۿ� fin�ϱ�
						readCnt++;
						buffer.insert(buffer.begin() + minIndex, s); //�ּҰ� �ڸ��� ������ �ֱ�
						cout << "�ּҰ� �ڸ��� [" << s << "]�� �־����ϴ�." << endl;
					}
				}
				cout << "�޸� �� ������: ";
				for (int i = 0; i < memory.size(); i++) {
					cout << memory.at(i) << ' ';
				}
				cout << endl;

				cout << "freeze Ȯ��: ";
				for (int i = 0; i < freeze.size(); i++) {
					cout << freeze.at(i) << ' ';
				}
				cout << endl;

				cout << "���ο� ���� Ȯ�ο�: "; //��� 6
				for (int i = 0; i < buffer.size(); i++) {
					cout << buffer.at(i) << ' ';
				}
				cout << endl << endl;

				freeze_count++;
			}
			//buffer_flag = false;

			cout << "run_print.size(): " << run_print.size() << endl;

			for (int i = 0; i < run_print.size(); i++) {  //run_print Ȯ�ο�
				for (int j = 0; j < run_print.at(i).size(); j++) {
					cout << run_print.at(i).at(j) << ' ';
				}
				cout << endl;
			}
			cout << endl;

			run_print.push_back(memory); //run�� memory����
			memory.clear(); //���ο� ������ ���� memory ����
			buffer.clear(); //���� ���̽��� ���� ����
		}
		cout << "Run" << endl;
		cout << run_print.size() << endl;
		fout << run_print.size() << endl;
		for (int i = 0; i < run_print.size(); i++) {
			for (int j = 0; j < run_print[i].size(); j++) {
				cout << run_print[i][j] << ' ';
				fout << run_print[i][j] << ' ';
			}
			cout << endl;
			fout << endl;
		}
		cout << "=======================case clear=======================" << endl << endl;
		run_print.clear();
	}

	fin.close();
	fout.close();

	system("pause");
	return 0;
}