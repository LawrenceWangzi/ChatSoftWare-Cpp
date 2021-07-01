#ifndef USERKEY
#define USERKEY
#include <arpa/inet.h>
#include <string>
using namespace std;

struct UserInformation//登陆用户信息或者注册用户信息
{
	char RegisterIndexName[20] = {0};//登陆账号
	char RegisterPwd[20] = {0};//登陆密码
	int RegisterFlag;//标志 0 1
};
class UserKey
{
public:
	UserKey(){};
	UserKey(string KeyIndex,string KeyName,int KeyCsockfd);
	~UserKey();

	string KeyIndex;
	string KeyName;
	int KeyCsockfd;

};


#endif //USERKEY


