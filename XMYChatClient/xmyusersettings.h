#ifndef XMYUSERSETTINGS_H
#define XMYUSERSETTINGS_H

#define USER_CONFIG_FILE ".\\.config.ini"

#include <QObject>
#include <QSettings>

class xmyUserSettings : public QObject
{
    Q_OBJECT
public:
    explicit xmyUserSettings(QObject *parent = nullptr);
    bool get_value(QString key, QVariant&value);
    void set_value(QString key, QVariant value);


signals:

private:
    QSettings settings;
};

#endif // XMYUSERSETTINGS_H
