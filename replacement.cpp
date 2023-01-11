#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace std;
#pragma warning ( disable : 4996 )

#define M 5 //사용할 메모리 개수

int test_case;
int sort_num;
int s; //읽어오는 값

vector<int>buffer; //tast할 데이터를 읽어올 곳
vector<int>memory; //정렬한 데이터를 담을 곳
vector<int>freeze; //동결된 데이터를 담을 곳
vector<int>unfrozen; //동결 해제를 위한 벡터
vector<vector<int>>run_print;

vector<int>F = { 1000, 1000, 1000, 1000, 1000 };

int main(void) {
	ifstream fin;
	fin.open("replacement_input.txt");
	ofstream fout;
	fout.open("replacement_output.txt");

	if (!fin) {
		cerr << "파일 열기 실패"; return 0;
	}
	if (!fout) {
		cerr << "파일 열기 실패"; return 0;
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

		while (buffer != F) { //정렬될때까지 반복
			cout << buffer_loop_count << "번째" << endl;
			cout << "읽은 횟수: " << readCnt << endl;

			//테스트용 출력 3
			cout << "버퍼에 잘 들어갔는지: ";
			for (int i = 0; i < M; i++) {
				cout << buffer.at(i) << ' ';
			}
			cout << endl;

			int min;

			min = *min_element(buffer.begin(), buffer.end());
			cout << "최소값: " << min << endl; //출력4
			int minIndex = find(buffer.begin(), buffer.end(), min) - buffer.begin();
			cout << "최소값 인덱스: " << minIndex << endl; //최소값의 인덱스 |출력5

			if (buffer_loop_count == 1) {
				memory.push_back(min); //메모리에 저장

				fin >> s; //버퍼에 fin하기
				readCnt++;
				buffer.erase(buffer.begin() + minIndex); //최소값 삭제
				cout << "최소값을 삭제했습니다." << endl;
				buffer.insert(buffer.begin() + minIndex, s); //최소값 자리에 다음값 넣기
				cout << "최소값 자리에 [" << s << "]을 넣었습니다." << endl;
			}
			else if (min < memory.back()) {
				freeze.push_back(min);
				buffer.at(minIndex) = 1000; //freeze 된 인덱스는 빼고 진행하기 위해
				cout << "최소값 자리에 [1000]을 넣었습니다." << endl;
			}
			else {
				memory.push_back(min); //메모리에 저장

				buffer.erase(buffer.begin() + minIndex); //최소값 삭제
				cout << "최소값을 삭제했습니다." << endl;
				if (readCnt == sort_num) { // 다 읽었다면
					buffer.insert(buffer.begin() + minIndex, 1000); //최소값 자리에 1000넣기
					cout << "최소값 자리에 [" << s << "]을 넣었습니다." << endl;
				}
				else { // 아직 덜 읽었다면
					fin >> s; //버퍼에 fin하기
					readCnt++;
					buffer.insert(buffer.begin() + minIndex, s); //최소값 자리에 다음값 넣기
					cout << "최소값 자리에 [" << s << "]을 넣었습니다." << endl;
				}
			}
			cout << "메모리 잘 들어갔는지: ";
			for (int i = 0; i < memory.size(); i++) {
				cout << memory.at(i) << ' ';
			}
			cout << endl;

			cout << "freeze 확인: ";
			for (int i = 0; i < freeze.size(); i++) {
				cout << freeze.at(i) << ' ';
			}
			cout << endl;

			cout << "새로운 버퍼 확인용: "; //출력 6
			for (int i = 0; i < buffer.size(); i++) {
				cout << buffer.at(i) << ' ';
			}
			cout << endl << endl;

			buffer_loop_count++;
		}
		run_print.push_back(memory); //run에 memory저장
		memory.clear(); //새로운 정렬을 위해 memory 비우기
		buffer.clear(); //새로 담기 위해 비워


		// 이제 다시 새로 시작


		bool read_complete_flag = true;
		//bool buffer_flag = true;
		while (read_complete_flag || !freeze.empty()) {
			//buffer_flag = true;
			for (int i = 0; i < freeze.size(); i++) { //freeze된 것들 unfrozen으로 옮기기
				unfrozen.push_back(freeze.at(i));
			}
			freeze.clear(); //옮겼으니까 freeze 비워

			cout << "unfrozen.size(): " << unfrozen.size() << endl;

			for (int i = 0; i < unfrozen.size(); i++) {  //unfrozen 확인용
				cout << unfrozen.at(i) << ' ';
			}
			cout << endl;

			cout << "------------------------------------동결 해제------------------------------------" << endl;

			freeze.clear();

			for (int i = 0; i < run_print.size(); i++) {  //run_print 확인용
				for (int j = 0; j < run_print.at(i).size(); j++) {
					cout << run_print.at(i).at(j) << ' ';
				}
				cout << endl;
			}

			//위에 반복문이랑 동일 (freeze버전)
			int freeze_count = 1;
			while (buffer != F) { //freeze 해제 후 다시 정렬
				cout << freeze_count << "번째" << endl;
				cout << "읽은 횟수: " << readCnt << endl;
				cout << endl;
				if (freeze_count == 1) {
					if (unfrozen.size() < M) { // 5개보다 작으면 5개 못 읽어오니까 개수만큼 읽고 정렬
						cout << "5보다 작을 때" << endl;
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
					else { // 5개 이상이면 위에랑 똑같이 ㄱ
						cout << "5개일 때" << endl;
						for (int i = 0; i < M; i++) {
							buffer.push_back(unfrozen.at(i));
						}
					}
					unfrozen.clear();
				}

				cout << "버퍼에 잘 들어갔는지: ";
				for (int i = 0; i < buffer.size(); i++) {
					cout << buffer.at(i) << ' ';
				}
				cout << endl;

				int min;

				min = *min_element(buffer.begin(), buffer.end());
				cout << "최소값: " << min << endl; //출력4
				int minIndex = find(buffer.begin(), buffer.end(), min) - buffer.begin();
				cout << "최소값 인덱스: " << minIndex << endl; //최소값의 인덱스 |출력5

				buffer.erase(buffer.begin() + minIndex); //최소값 삭제
				cout << "최소값을 삭제했습니다." << endl;
				if (freeze_count == 1) { //첫번째일때만
					memory.push_back(min); //메모리에 저장
					if (readCnt == sort_num) { // 다 읽었다면
						read_complete_flag = false;
						buffer.insert(buffer.begin() + minIndex, 1000); //최소값 자리에 1000넣기
						cout << "최소값 자리에 [1000]을 넣었습니다." << endl;
					}
					else { // 아직 덜 읽었다면
						fin >> s; //버퍼에 fin하기
						readCnt++;
						buffer.insert(buffer.begin() + minIndex, s); //최소값 자리에 다음값 넣기
						cout << "최소값 자리에 [" << s << "]을 넣었습니다." << endl;
					}
				}
				else if (min < memory.back()) {
					freeze.push_back(min);
					buffer.insert(buffer.begin() + minIndex, 1000); //최소값 자리에 1000넣기
					//buffer.at(minIndex) = 1000; //freeze 된 인덱스는 빼고 진행하기 위해
					cout << "최소값 자리에 [1000]을 넣었습니다." << endl;
				}
				else {
					memory.push_back(min); //메모리에 저장
					if (readCnt == sort_num) { // 다 읽었다면
						cout << "다 읽었습니다." << endl;
						read_complete_flag = false;
						buffer.insert(buffer.begin() + minIndex, 1000); //최소값 자리에 1000넣기
						cout << "최소값 자리에 [1000]을 넣었습니다." << endl;
					}
					else { // 아직 덜 읽었다면
						fin >> s; //버퍼에 fin하기
						readCnt++;
						buffer.insert(buffer.begin() + minIndex, s); //최소값 자리에 다음값 넣기
						cout << "최소값 자리에 [" << s << "]을 넣었습니다." << endl;
					}
				}
				cout << "메모리 잘 들어갔는지: ";
				for (int i = 0; i < memory.size(); i++) {
					cout << memory.at(i) << ' ';
				}
				cout << endl;

				cout << "freeze 확인: ";
				for (int i = 0; i < freeze.size(); i++) {
					cout << freeze.at(i) << ' ';
				}
				cout << endl;

				cout << "새로운 버퍼 확인용: "; //출력 6
				for (int i = 0; i < buffer.size(); i++) {
					cout << buffer.at(i) << ' ';
				}
				cout << endl << endl;

				freeze_count++;
			}
			//buffer_flag = false;

			cout << "run_print.size(): " << run_print.size() << endl;

			for (int i = 0; i < run_print.size(); i++) {  //run_print 확인용
				for (int j = 0; j < run_print.at(i).size(); j++) {
					cout << run_print.at(i).at(j) << ' ';
				}
				cout << endl;
			}
			cout << endl;

			run_print.push_back(memory); //run에 memory저장
			memory.clear(); //새로운 정렬을 위해 memory 비우기
			buffer.clear(); //다음 케이스를 위해 비우기
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