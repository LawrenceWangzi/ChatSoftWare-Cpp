#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H 
#include <mysql/mysql.h>
#include <iostream>
#include <cstring>
#include <stdio.h>

class MysqlDataBase
{
public:
	MysqlDataBase(const char* SQLhost, const char* SQLuser, const char* SQLpasswd, const char* SQLdbName);
	~MysqlDataBase();

	int ConnectDataBase();
	void CloseDataBase();
	void InsertDataBase(const char* SQLstring);
	MYSQL_ROW SelectDataBase(const char* SQLstring);
private:
	MYSQL PrivateMysql;

	const char* SQLhost;
	const char* SQLuser;
	const char* SQLpasswd;
	const char* SQLdbName;

};



#endif //MYSQLDATABASE_H

