#ifndef MESSAGE
#define MESSAGE
struct Message
{
	int TheToUserIndex;//���Ϊ0����ִ�������û�
	int TheFromUserIndex;
	char TheFromUserName[20];
	char message[256];//�����Ϣ���ַ�������
};

#endif // !MESSAGE
