#include <vector>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <random>

#pragma warning(disable: 4996)

SOCKET Connection;
using namespace std;

void mfiletovector(const string& filename, vector<string>& words) {
	ifstream file(filename);
	string word;
	while (file >> word) {
		words.push_back(word);
	}
	file.close();
};


void ClientHandler(int i) {
	setlocale(LC_ALL, "Russian");
	int msg_size; int connect, connect1;
	while (true) {
		connect1 = recv(Connection, (char*) & msg_size, sizeof(int), NULL);
		if (connect1 == SOCKET_ERROR) {
			cout << "Can't receive message from Server. Error # " << WSAGetLastError() << endl;
			closesocket(Connection);
			WSACleanup();
			break;
		}
		else {
			char* msg = new char[msg_size + 1];
			for (int i = 0; i < msg_size; i++) {
				msg[i] = 32;
			}
			msg[msg_size] = '\0';
			connect = recv(Connection, msg, msg_size, NULL);

			if (connect == SOCKET_ERROR) {
				cout << "Can't receive message from Server. Error # " << WSAGetLastError() << endl;
				closesocket(Connection);
				WSACleanup();
				break;
			}
			else {
				for (int i = 0; i < msg_size; i++) {
					cout << msg[i];
				}
				cout << endl;
				delete[] msg;
			}
		}
	}
}

int main(int argc, char* argv[]) {

	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.

	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

		Connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
			cout << "\n";
			return 1;
		}
		cout << "Connected!\n";
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

		char c;
		string msg1 = "";
		int bre = 0;
		int n = 1;
		while (true) {
			vector<string> gen1;
			vector<string> mid;
			mfiletovector("mid.txt", mid);
			mfiletovector("gen.txt", gen1);
			int midnum = gen() % 10;
			FILE* in1 = fopen("test.txt", "w");
			const string comm1 = gen1[gen() % gen1.size()];
			fprintf_s(in1, "%s\n", comm1.c_str());


			for (int k = 0; k < midnum; k++) {
				const string comm2 = mid[gen() % mid.size()];
				fprintf_s(in1, "%s\n", comm2.c_str());
			}
			fprintf(in1, "clear();");
			fclose(in1);

			FILE* in = fopen("test.txt", "r");
			fscanf_s(in, "%c", &c, 1);
			while (c != 59) { msg1.append(1, c); fscanf_s(in, "%c", &c, 1); }
			if (msg1 != "") {
				int msg_size = msg1.size();
				send(Connection, (char*)&msg_size, sizeof(int), NULL);
				send(Connection, msg1.c_str(), msg_size, NULL);
				msg1.clear();
			}
			Sleep(3000);
			fclose(in);

		}
	

	system("pause");
	return 0;
}