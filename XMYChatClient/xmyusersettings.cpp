#include "xmyusersettings.h"

xmyUserSettings::xmyUserSettings(QObject *parent) : QObject(parent)
  ,settings(QSettings(USER_CONFIG_FILE, QSettings::IniFormat))
{

}

bool xmyUserSettings::get_value(QString key, QVariant &value)
{
    if(!settings.contains(key)) return false;
    value=settings.value(key).toString();
    return true;
}

void xmyUserSettings::set_value(QString key, QVariant value)
{
    settings.setValue(key,value);
}
