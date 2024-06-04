#include "base.h"
#pragma warning(suppress : 4996)
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;
#include <iostream>
#include <sstream>
//#include <curl/curl.h>

// Определимся с номером порта и другими константами.
#define PORT    5555
#define BUFLEN  4096


string urlDecode(string& SRC) {
    string ret;
    char ch;
    int i, ii;
    for (i = 0; i < SRC.length(); i++) {
        if (SRC[i] == '%') {
            sscanf(SRC.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        }
        else {
            ret += SRC[i];
        }
    }
    return (ret);
}

// Две вспомогательные функции для чтения/записи (см. ниже)
int   readFromClientHTTP(int fd, char* buf);
void  writeToClientHTTP(int fd, string buf);

client_data cl;


int  main(void)
{
    client_data dt;
    int     i, err, opt = 1;
    int     sock, new_sock;
    fd_set  active_set, read_set;
    struct  sockaddr_in  addr;
    struct  sockaddr_in  client;
    char    buf[BUFLEN];
    string buff;
    socklen_t  size;

    printf("http SERVER\n");

    // Инициализация windows sockets
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Создаем TCP сокет для приема запросов на соединение
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Server: cannot create socket");
        exit(EXIT_FAILURE);
    }
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // Заполняем адресную структуру и
    // связываем сокет с любым адресом
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (err < 0) {
        perror("Server: cannot bind socket");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Создаем очередь на 3 входящих запроса соединения
    err = listen(sock, 3);
    if (err < 0) {
        perror("Server: listen queue failure");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Подготавливаем множества дескрипторов каналов ввода-вывода.
    // Для простоты не вычисляем максимальное значение дескриптора,
    // а далее будем проверять все дескрипторы вплоть до максимально
    // возможного значения FD_SETSIZE.
    FD_ZERO(&active_set);
    FD_SET(sock, &active_set);

    // Основной бесконечный цикл проверки состояния сокетов
    while (1) {
        // Проверим, не появились ли данные в каком-либо сокете.
        // В нашем варианте ждем до фактического появления данных.
        read_set = active_set;
        if (select(FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0) {
            perror("Server: select  failure");
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        // fd_set в windows устроена немного иначе - как массив дескрипторов
        // Данные появились. Проверим в каком сокете.
        for (int j = 0; j < read_set.fd_count; j++) {
            i = read_set.fd_array[j];
            if (FD_ISSET(i, &read_set)) {
                if (i == sock) {
                    // пришел запрос на новое соединение
                    size = sizeof(client);
                    new_sock = accept(sock, (struct sockaddr*)&client, &size);
                    if (new_sock < 0) {
                        perror("accept");
                        WSACleanup();
                        exit(EXIT_FAILURE);
                    }
                    fprintf(stdout, "Server: connect from host %s, port %hu.\n",
                        inet_ntoa(client.sin_addr),
                        ntohs(client.sin_port));
                    FD_SET(new_sock, &active_set);
                    fprintf(stdout, "new socket = %d\n", new_sock);
                }
                else {
                    // пришли данные в уже существующем соединени
                    fprintf(stdout, "socket = %d\n", i);
                    err = readFromClientHTTP(i, buf);
                    if (err < 0) {
                        // ошибка или конец данных
                        closesocket(i);
                        fprintf(stdout, "close socket = %d\n", i);
                    }
                    else {
                        buff = "";
                        for (int j = 0; j < 4096; j++) { buff.append(1, buf[j]); }
                        writeToClientHTTP(i, buff);
                    }
                    FD_CLR(i, &active_set);
                }
            }
        }
    }
    WSACleanup();
}

// прочитать весь запрос от клиента и положить его в buf
// надеемся что запрос поместится в BUFLEN

int  readFromClientHTTP(int fd, char* buf)
{
    int  nbytes;

    nbytes = recv(fd, buf, BUFLEN, 0);
    fprintf(stdout, "reading %d bytes from socket %d\n", nbytes, fd);
    if (nbytes < 0) {
        // ошибка чтения
        int err = WSAGetLastError();
        printf("Socket read error %d\n", err);
        return -1;
    }
    else {
        // есть данные
        printf("\n\nServer gets %d bytes:\n", nbytes);
        // поставим 0 в конце прочитанных данных
        buf[min(nbytes, BUFLEN - 1)] = 0;
        printf("%s\n", buf);
        return nbytes;
    }
}



#include <time.h>

void ProcessHTML(stringstream& html, const string &request)
{
    /*
    char tbuf[64];   // время, когда обрабатываем этот запрос
    time_t ttt;      // можем потом поставить в заголовок ответа сервера
    time(&ttt);
    ctime_s(tbuf, 256, &ttt);
    printf("%s\n",tbuf);
    */

    ifstream file(request);
    
    html << "<!DOCTYPE html>\r\n";
    html << "<html><head><meta charset = \"cp1251\">\r\n";
    html << "<title>Учебный сервер</title></head>\r\n";
    html << "<body>\r\n";
    html << "<h2>MyBase(cpp)</h2>\r\n";
    html << "<form name=\"myform\" action=\"http://localhost:5555\"  method=\"post\">\r\n";
    //html << "<form name=\"myform\" action=\"http://localhost:5555\"  method=\"get\">\r\n";
    html << "<input name=\"request\" type=\"text\" width=\"20\"> request<br>\r\n";
    html << "<input name=\"sub\" type=\"submit\" value=\"Send\">\r\n";
    html << "</form>\r\n";
    string msg2 = "";
    while (getline(file, msg2))
    {
        html <<"<p>"<< msg2 << "<\p>\r\n";
    } file.close();
    //html << "<input name=\"comment\" type=\"text\" width=\"20\" value=\"" << tbuf << "\"> comment<br>\r\n";
    html << "</body></html>\r\n";
}


//  простейший разбор запроса и отправление ответа

void  writeToClientHTTP(int fd, string buff)
{
    int msg_size = buff.size();
    char* buf=new char[msg_size];
    for (int j = 0; j < msg_size; j++) {
        buf[j] = buff[j];
    }
    int  nbytes;
    stringstream head;
    stringstream html;
    string request = "";   // строка параметров запроса

    if (strstr(buf, "GET")) {  // здесь параметры в первой строке после /
        char* p1 = strchr(buf, '/');
        char* p2 = strchr(p1, ' ');
        *p2 = 0;
        request = p1;
        printf("get request: %s\n", request.c_str());
        *p2 = ' ';
    }
    if (strstr(buf, "POST")) {  // здесь параметры после всего заголовка после пустой строки
        char* p1 = strstr(buf, "\r\n\r\n");
        request = (p1 + 4);
        printf("post request: %s\n", request.c_str());
    }

    // ответ на нераспознанные запросы 
    // не совсем аккуратно, чтобы не загромождать ...
    // отбрасывает непустые GET запросы, в которых нет параметра "request"

    if (request != "/" && request.find("request") == string::npos) {
        head << "HTTP/1.1 404 Not found\r\n";
        head << "Connection: close\r\n";
        head << "Content-length: 0\r\n";
        head << "\r\n";
        nbytes = send(fd, head.str().c_str(), head.str().length() + 1, 0);
        return;
    }

    // ответ на распознанные запросы
    // формирование HTML

    request = urlDecode(request);
    string req="";
    for (int j = 8; j < request.size(); j++) {
        if (request[j] != 38 || request[j + 1] != 115 || request[j+2]!=117) {
            req.append(1, request[j]);
        }
        else { break; }
    }

    string bu = "";
    FILE* out = fopen("out2.txt", "w");
    FILE* in1 = fopen("in.txt", "w");
    for (int i = 0; i < req.size(); i++) {
        fprintf(in1, "%c", req[i]);
    }
    fclose(in1);
    FILE* in = fopen("in.txt", "r");
    cl.imput(cl, out, in);
    fclose(in);
    fclose(out);

    
    cout << "//" << request << "//" << endl;
    cout <<"//"<< req<<"//"<<endl;
    ProcessHTML(html, "out2.txt");
    int html_length = html.str().length();

    // формирование HTTP заголовка
    head << "HTTP/1.1 200 OK\r\n";
    head << "Connection: keep-alive\r\n";
    head << "Content-type: text/html\r\n";
    head << "Content-length: " << html_length << "\r\n";
    head << "\r\n";

    // вывод заголовка и html
    nbytes = send(fd, head.str().c_str(), head.str().length() + 1, 0);
    printf("http nb = %d\n", nbytes);
    nbytes = send(fd, html.str().c_str(), html.str().length() + 1, 0);
    printf("html nb = %d\n", nbytes);


    // для контроля того, что отправили
    //cout << "Write back\n";
    //cout << head.str();
    //cout << html.str();

    if (nbytes < 0) {
        perror("Server: write failure");
    }
}

/*
cout << "operating" << endl;
FILE* out = fopen("out2.txt", "w");
FILE* in1 = fopen("in.txt", "w");
for (int i = 0; i < 4096; i++) {
    fprintf(in1, "%c", buf[i]);
}
fclose(in1);
FILE* in = fopen("in.txt", "r");
cl.imput(cl, out, in);
fclose(in);
fclose(out);

ifstream out1("out2.txt");
string buff = ""; string msg2 = "";
while (getline(out1, msg2))
{
    buff.append(msg2); buff.append("\n");
}
out1.close();

cout << "////" << endl << buf << "////" << endl*/