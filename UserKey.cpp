#include "UserKey.h"


UserKey::UserKey(string KeyIndex, string KeyName, int KeyCsockfd):
KeyIndex(KeyIndex), KeyName(KeyName), KeyCsockfd(KeyCsockfd)
{
}


UserKey::~UserKey()
{
}
