#include "xmy_utilities.h"

XMY_Utilities::XMY_Utilities()
{

}

QString XMY_Utilities::base64tomd5(QString base64) {
    return QCryptographicHash::hash(base64.toUtf8(),QCryptographicHash::Md5).toHex();
}

QString XMY_Utilities::pixmaptomd5(QPixmap pic) {
    QByteArray ba;
    QBuffer buf(&ba);
    pic.save(&buf,"png");
    return QCryptographicHash::hash(ba,QCryptographicHash::Md5).toHex();
}

QString XMY_Utilities::emailtomd5(QString email)
{
    return QCryptographicHash::hash(email.trimmed().toLower().toUtf8(),QCryptographicHash::Md5).toHex();
}

bool XMY_Utilities::checkDir(QString path)
{
    QDir dir(path);
    if(dir.exists()) {
        return true;
    }
    else return QDir(".").mkpath(path);
}

void XMY_Utilities::save_pic_from_base64(QString base64, QString filename)
{
    QByteArray picbytes=QByteArray::fromBase64(base64.toLocal8Bit());
    QBuffer buf(&picbytes);
    buf.open(QIODevice::WriteOnly);
    QPixmap pic;
    pic.loadFromData(picbytes);
    pic.save(filename);

}

QString XMY_Utilities::get_pic_base64(QString filename)
{
    QPixmap avatar(filename);
    QByteArray ba;
    QBuffer buf(&ba);
    avatar.save(&buf,"png");
    return ba.toBase64();
}

QString XMY_Utilities::get_avatar_filename(QString path, QString email)
{
    QString filename=path+emailtomd5(email)+".png";
    if(path==".avatar\\" && !QFile(filename).exists()) filename=path+"default.png";
    return filename;
}

bool XMY_Utilities::check_valid_email(QString email)
{
    QRegularExpression re("[a-zA-z0-9]+\\@[a-zA-z0-9]+\\.[a-zA-z0-9]+");
    return re.match(email).hasMatch();
}

QString XMY_Utilities::get_time_string()
{
    return QDateTime::currentDateTime().toString("hh:mm:ss yyyy.MM.dd");
}
