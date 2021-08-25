#ifndef XMY_DATABASE_H
#define XMY_DATABASE_H

#include <QObject>

class XMY_database : public QObject
{
    Q_OBJECT
public:
    explicit XMY_database(QObject *parent = nullptr);

signals:

};

#endif // XMY_DATABASE_H
