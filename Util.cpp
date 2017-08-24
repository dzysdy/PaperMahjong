#include "Util.h"
#include <QDir>

QString Util::getResourcePath()
{
    //return "/home/dzy/code/private/PaperMahjong/resource/";
    return QDir::currentPath() + "/resource/";
}
