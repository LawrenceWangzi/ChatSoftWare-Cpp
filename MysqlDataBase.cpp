#include "MysqlDataBase.h"

MysqlDataBase::MysqlDataBase(const char* SQLhost, const char* SQLuser, const char* SQLpasswd, const char* SQLdbName)
:SQLhost(SQLhost), SQLuser(SQLuser), SQLpasswd(SQLpasswd), SQLdbName(SQLdbName)

{
}


MysqlDataBase::~MysqlDataBase()
{
}

int MysqlDataBase::ConnectDataBase()
{
	if (NULL == mysql_init(&PrivateMysql))
	{
		cout << "this will init mysql" << mysql_error(&PrivateMysql) << endl;
		return -1;
	}
	if (NULL==mysql_real_connect(&PrivateMysql,SQLhost,SQLuser,SQLpasswd,SQLdbName,0,NULL,0))
	{
		cout << "this will connect mysql" << mysql_error(&PrivateMysql) << endl;
		return -1;
	}

	cout << "connected the mysql successful!\n" << endl;
	return 0;
}

void MysqlDataBase::InsertDataBase(const char* SQLstring)
{
	int QueryFlag = mysql_real_query(&PrivateMysql,SQLstring,strlen(SQLstring));
	if (QueryFlag!=0)
	{
		cout << "query the mysql "<<mysql_error(&PrivateMysql) << endl;
		return;
	}
}

MYSQL_ROW MysqlDataBase::SelectDataBase(const char* SQLstring)
{
	int QueryFlag = mysql_real_query(&PrivateMysql, SQLstring, strlen(SQLstring));
	if (QueryFlag != 0)
	{
		cout << "query the mysql " << mysql_error(&PrivateMysql) << endl;
		return NULL;
	}

	MYSQL_RES* Result = mysql_store_result(&PrivateMysql);
	if (NULL==Result)
	{
		printf("restore the result of mysql:%s\n",mysql_error(&PrivateMysql));
		return NULL;
	}
	MYSQL_ROW SQLrow = mysql_fetch_row(Result);
	return SQLrow;
}

void MysqlDataBase::CloseDataBase()
{
	mysql_close(&PrivateMysql);
}

