#include "base.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <stdio.h>
#include <random>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>

#pragma warning(disable: 4996)

vector<int> ind;
vector<SOCKET> Connections;
int Counter = 0;
client_data cl;
mutex access;

using namespace std;

char fixchar(char c) {
	char c1=c;
	if (c == -16) { c1 = -88; return c1; }
	if (c == -15) { c1 = -72; return c1; }
	if (c >= -128 && c <= -81) { c1 = c + 64; return c1; }
	if (c >= -32 && c <= -17) { c1 = c + 16; return c1; }
}


void ClientHandler(int index) {
	int msg_size; int connect, connect1; int st = 0;
	setlocale(LC_ALL, "Russian");
	while (st == 0) {
		connect1 = recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);

		if (connect1 == SOCKET_ERROR) {
			cout << "Can't receive message from Client. Error # " << WSAGetLastError() << " index #" << index << endl;
			closesocket(Connections[index]);
			for (auto i = ind.begin(); i != ind.end(); i++) { if (*i == index) { ind.erase(i); break; } }
			st = 1;
		}
		else {
			char* msg = new char[msg_size + 1];
			msg[msg_size] = '\0';

			connect = recv(Connections[index], msg, msg_size, NULL);

			access.lock();

			if (connect == SOCKET_ERROR) {
				cout << "Can't receive message from Client. Error # " << WSAGetLastError() << " index #" << index << endl;
				closesocket(Connections[index]);
				for (auto i = ind.begin(); i != ind.end(); i++) { if (*i == index) { ind.erase(i); break; } }
				access.unlock();
				st = 1;
			}
			else {
				FILE* out = fopen("out2.txt", "w");
				FILE* in1 = fopen("in.txt", "w");
				FILE* log = fopen("log.txt", "a");
				//cout << msg_size;
				for (int i = 0; i < msg_size; i++) {
					fprintf(in1, "%c", msg[i]);
					fprintf(log, "%c", fixchar(msg[i]));
				}
				fprintf(log, "\n");
				fclose(log);
				fclose(in1);
				FILE* in = fopen("in.txt", "r");
				cl.imput(cl, out, in);
				fclose(in);
				fclose(out);
				ifstream out1("out2.txt");
				string msg1 = ""; string msg2 = "";
				while (getline(out1, msg1))
				{
					msg2.append(msg1); msg2.append("\n");
				}
				out1.close();
				int msg_size = msg2.size();

				for (auto i = ind.begin(); i!=ind.end(); i++) {
					if (*i != index) {
						/*string msgi = "client command complete";
						int msg_size1 = msgi.size();
						send(Connections[*i], (char*)&msg_size1, sizeof(int), NULL);
						send(Connections[*i], msgi.c_str(), msg_size1, NULL);*/
						continue;
					}

					cout << "command complete, client num:" << *i + 1 << "\n";
					send(Connections[*i], (char*)&msg_size, sizeof(int), NULL);
					send(Connections[*i], msg2.c_str(), msg_size, NULL);

				}
				delete[] msg;
			}

			access.unlock();
		}
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	FILE* log = fopen("log.txt", "a");
	fprintf(log, "\n//\n\n");
	fclose(log);

	client_data cl;
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100000; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == INVALID_SOCKET) {
			//cout << "Client detected, but can't connect to a client. Error # " << WSAGetLastError() << endl;
			closesocket(sListen);
			closesocket(newConnection);
		}
		else {
			std::cout << "Client Connected!\n";
			std::string msg = "\n";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);

			Connections.push_back(newConnection);
			ind.push_back(i);
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}

	WSACleanup();
	system("pause");
	return 0;
}
/*
int main()
{
	setlocale(LC_ALL, "Russian");
	int n,i;
	client_data clients;
	printf("Размер базы данных: ");
	cin >> n;
	cout << "\n";

	clients.generate_base(n);
	clients.print_base();
	//clients.print_base_file("out");
	cout << "next base.........................................................................\n"; cout << "\n\n";

	//clients.getlen();
	clients.delete_cl(3);
	clients.print_base();
	//clients.print_base_file("out");
	cout << "0()next base.........................................................................\n"; cout << "\n\n";

	int arr1[3] = { 29,9,2004 };
	int arr11[3] = { 1,1,2000 };
	vector<double> prod1 = { 95699.55, 120499.99 };
	double avg1 = (95699.55 + 120499.99) / 2;
	double sum1 = 95699.55 + 120499.99;
	vector<double> prod11 = { 95699.55, 120499.99,501000.9 };

	//clients.getlen();
	clients.edit_cl(5,"Морозов","Андрей","Александрович",arr1,79175294117,prod1);
	clients.edit_cl(6, "Жепчанов", "Константин", "Холович", arr1, 79175554678, prod1);
	clients.edit_cl("Жепчанов", "Константин", "Холович","Штольц","Александр","Владимирович", arr1, 79175554678, prod11);
	clients.delete_cl("Жепчанов", "Константин", "Холович");
	clients.print_base();

	cout << "1()next base.........................................................................\n"; cout << "\n\n";

	(clients.correct()).print_base_file("out2.txt");
	clients.sortby_date();
	clients.print_base();
	clients.print_base_file("out");

	cout << "2()next base.........................................................................\n"; cout << "\n\n";

	client_data oldclients;
	oldclients = clients.select_(arr1,avg1,sum1,79175294117);
	//oldclients.print_base_file("out2.txt");
	oldclients.print_base();

	cout << "3()imput section.........................................................................\n"; //cout << "\n\n";
	cout << "..................................................................................\n"; cout << "\n\n";
	client_data cl;
	cl.imput(clients);
	return 0;
}*/
//out select(1.1.2000, 24.12.2022 / )()()()(200000,1000000)()
//out select(1.1.2000, 24.12.2022 / )()()()(200000,1000000)()