#ifndef XMY_UTILITIES_H
#define XMY_UTILITIES_H

#include "xmy_basic.h"

class XMY_Utilities
{
public:
    XMY_Utilities();
    static QString base64tomd5(QString base64);
    static QString pixmaptomd5(QPixmap pic);
    static QString emailtomd5(QString email);
    static bool checkDir(QString path);
    static void save_pic_from_base64(QString base64, QString filename);
    static QString get_pic_base64(QString filename);
    static QString get_avatar_filename(QString path, QString email);
    static bool check_valid_email(QString email);
    static QString get_time_string();
};

#endif // XMY_UTILITIES_H
