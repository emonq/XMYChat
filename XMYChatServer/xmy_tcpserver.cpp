#include "xmy_tcpserver.h"



XMY_tcpserver::XMY_tcpserver(QObject *parent) : QTcpServer(parent)
{
    db=new XMY_database;
    connect(db,&XMY_database::new_log,this,&XMY_tcpserver::new_log);
    if(!QFile(".avatar\\default.png").exists()) {
        QString default_avatar="iVBORw0KGgoAAAANSUhEUgAAASwAAAEsCAIAAAD2HxkiAAAM0klEQVR4nO3dbW/ixhqAYZc5dWoEgtqBvIgNK0Xa//97NtooqCkQiCmU1Oxanep8sLTdbjbJ2Nh+Zuz7+nSkI3UfRb494xfgp81m4wGQ05EeAGg7IgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSE/U96ABhJ0zRJks+fPydJorX2PO/vv/8+HA7Z/6uU6na72f/+5ZdfTk5Out1ur9cTGxd5/LTZbKRnwI+labrdbne73dfw8gqCoNvtDgaD4XBY+ngoCxFaJ0mSP//8848//vi60B1PKdXv97MalVJl/WdRCiK0yHa7Xa/X+/2+un9CKRWG4dnZme/71f0ryIUI5Wmtt9vtYrFI07S2fzSKotFo9PVKEoKIUFgcx/f398Uu+Y43HA4nkwmroiwiFJMkye+//17p5tOEUurs7Oz8/Fx2jDYjQgFa6/l8vl6vpQf5l+/7k8mEm6giiLBuSZLc3t7WeflnbjQavXv3TnqK1iHCWq1Wq/v7e+kpXhMEwfX1NVeJdSLCmmitZ7PZdruVHuRtSqnpdMrWtDa8O1oHrfXHjx+dKNDzPK317e0tZ+fasBJWLkmSm5sbqYcQx4iiaDqdSk/RfKyE1XK3QM/z4jiezWbSUzQfEVbI6QIzdFgDIqxKAwrM0GHViLASaZo2o8BM9m6d9BSNRYTl01p/+vSpMQVmVqsV9/AqQoQly55GlPhRQHvc3d3RYRWIsGSLxaKRBWZ+++23JEmkp2gaIizTdrtdrVbSU1Qoe+9HeoqmIcLSpGnahgP0cDhwk6ZcRFia5t2MeclqtXLlFTwnEGE55vN5gy8Fn5vNZi0549SACEuQpulyuZSeolZaazalZSHCErThUvC5OI7Fv5ujGYjwWNvttrXHYjvPPqUjwqO0/JZ9mqbz+Vx6CucR4VEeHh5afn9ivV63/C9wPCIsTmtt1TemidBaPzw8SE/hNiIsjmUww2J4JCIsiGXwKxbDIxFhQSyD32IxPAYRFsEy+B0Ww2MQYRG73Y4T/3f4qGFhRFgEZ/3nst8Vlp7CSUSYW5IkrXpX21wcx9IjOIkIc+Nq8CW73c7OH7qxHBHmxqbrFY+Pj9IjuIcI89lsNtySeQW3Zwogwnxa+4EJQ2masiPNiwjzYS/6Jv5EeRFhDkmSsBd9ExHmRYQ5cMFj4unpiVNVLkSYAxeEhna7nfQILiFCU1prntEb4myVCxGa4uvfzfG3yoUITXF2N8eWIRciNPX09CQ9gks4Z5kjQlOc3XPhz2WOCI2kacpt91yI0BwRGvny5Yv0CI7h3ow5IjTCFU5erITmiBBVYQNviAiNcGu0AHakhogQVWElNESERlgJC2AlNESEgDAifBsfFS+GG6SGiPBtPCQshmtCQ0QICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUT4tpOTE+kRnMTfzRARvs33fekRnPTzzz9Lj+AGIjTS6/WkR3BPv9+XHsENRGhEKSU9gnvYjhoiQiNBEEiP4B628YaI0Ei325UewTFs4M0RoREub/IiQnNEaEQpxY40F05b5ojQFEdVLvy5zBGhKfZX5gaDgfQILiFCU8PhUHoEZ/z666/SI7iECHPgBG+IP1QuRJgDJ3gTg8GAdxtyIcIcOMGb4FSVFxHmoJSiw9d1Op0wDKWncAwR5hNFkfQIVjs9PZUewT1EmM9wOOx0+KO9aDweS4/gHo6n3DjZv2QwGPDSdgFEmBsn+5fwlymGCHPzfZ/bM8/1ej1eVSuGCIvglP8cu/TCiLCIfr/Pxc+3fN/nyURhRFjQ5eWl9AgW4a9xDCIsKAxDFsNMEAQsg8cgwuI4/Wcmk4n0CG4jwuJYDD1uipaBCI/CYnhxcSE9gvOI8CgtXwyjKGIZPB4RHqu1i2Gn02EZLAURHisMw3Z+Edt4PG7zLqBERFiCFt4e9H3/7OxMeoqGIMIS9Pv9tn0X22Qy4TssykKE5Xj//r30CPUZDAZ891yJiLAcvu+35K3uTqfz7t076SkahQhLc3Fx0YYP3V9eXnI/plzNP2hqo5S6urqSnqJaQRC0ZMGvExGWqfGPK6bTqfQIDUSEJWvwYXp+fs7vNFaBCEvW7XYbuWHjwWB1iLB8FxcXzbt1MZ1OeTBYESIsn1KqYe/QjMdjXtSuDhFWYjgcNuYb2Xzf50XtShFhVd6/f9+Mx4ZsRKvWhKPETkqpBnzKiY1oDYiwQuPx2OkXu9mI1oMIq+X0ppSNaD1cPT5c4fu+o5vSwWDARrQeRFi58Xjs3LtsnU6nVR/OkkWEdXDuXbbxeMxGtDZEWIdut+vQT/y6u4V2FBHWZDQaSY9giu+0rxkR1qTb7bpyZchXV9SMCOvjxM3GTqfD55VqRoT1ceLBvRNnioYhwvo4cb/RlT1zkxBhfZzY5rES1o8I6+PESnhyciI9QusQIf6jed8JYD8irM9+v5ceATYiQkAYEdaHlRA/RIT1+euvv6RHeBtnivoRYU3SNHXi+N7tdtIjtA4R1kFr/enTJ+kpjMRxnCSJ9BTtQoSVS9P048ePh8NBehAjWuubmxs6rNNPm81GeoYmW61Wi8VCay09SG6Xl5fn5+fSU7QCEVYljuPFYpGmqfQgxQVBMJlMeJGtakRYMq11HMer1crp/L4VRVEjf13DHkRYmv1+v9lsttuti5vPN5FidYjwWGmabjabx8fHxix9rxgOh6PRiA1quYiwuAZc9RXj+/54PI6iyInPhdiPCHPTWq/X64eHh0ZuO3OJoigMQxbGIxFhDmmaLhaLOI6lB7GL7/unp6dhGHLFWAwRGtnv98vl0on3zgQNh8MwDPmytryI8A2tvfArTCkVhuHZ2RkLoyEi/DEu/I7X7/ezhZH7N68jwu9x4VcupVT2YMOJ77kSQYT/4sKvUkEQjMdjFsbniNDzPC970cyVDzq4jgcb32l1hNmFX0tedrFN9sR/OBxy/6alEWYXfk19z9MtPNhoXYT7/X69Xm+3W+lB8B++7w8Gg3Y+2GhRhFz4OSF7sOHQb6oer/kRcuHnouyJfxRFbXiw0eQIufBrgDY82GhmhFz4NUz2xL+pDzaaFiEXfs3WyI8yNiRCLvzapkmf8Xc+Qi782sz3/YuLC9dvpTocYZqm9/f3XPhBKTWdTt193O9qhMvlks8Z4Vv9fn86nbr4rN+9CJMkmc1m3HrBc44uiY79FsV+v7+5uaFA/JDW+vb21rl1xaWVcLPZ3N3dSU8BB0RRNJ1Opacw5cxKSIEwF8fxfD6XnsKUGxHu93sKRC7L5dKVXZ4DESZJcnt7Kz0F3HN3d+fEl5U4EOFsNuNRBIq5v7+XHuFttkc4n8+5F4rCDoeD/ReHVkeYpul6vZaeAm5bLpeWv1FsdYSO/tA0bLNYLKRHeI29EWqteS8UpYjj2Oazub0R8mooSvTw8CA9wovsjXC320mPgOaw+XCyNEKtNTdFUaLD4WDtxsrSCG0+b8FR1h5Ulkb4+fNn6RHQNNYeVJZG+PT0JD0Cmsbag8rSCIH2sDRCa6+h4S5rDypLI+TWKEpn7UFlaYRAexAhIIwIAWGWRtjpWDoY3GXtQWXpWG34VTrUzNqDytIIgfawNEJrT1pwl7UHlaURuviLArCctQeVpRE693MCsJ+1B5WlEfq+HwSB9BRojiAIWAlzc/2XH2EVmw8nqyO09sEO3NLpdIiwCKXU1dWV9BRogqurK6WU9BQvsjdCz/PCMOz1etJTwG29Xi8MQ+kpXmN1hJ7nXV9fc4cGhQVBcH19LT3FG2yPUCn14cMHOkQBQRB8+PDB5o1oxvYIPc9TSrEeIi9XCvTc+rns+Xy+XC6lp4ADzs/PLy8vpacw5VKEnuclSbJer+M4lh4EloqiaDQaWfua6A85FmEmTdPVavX4+PjPP/9IzwIrdDqd09PT8Xhs7Wsxr3Aywq/SNH16etrv91++fPEs/mJJlC57dnVyctLv93u9novtfeV2hEADOHB3FGg2IgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBBGhIAwIgSEESEgjAgBYUQICCNCQBgRAsKIEBD2fz0a4i5T03AEAAAAAElFTkSuQmCC";
        XMY_Utilities::checkDir(".avatar");
        XMY_Utilities::save_pic_from_base64(default_avatar,".avatar\\default.png");
    }
}

QList<QHostAddress> XMY_tcpserver::get_addr()
{
    QList<QHostAddress> ip;
    QString hostname;
    QHostInfo hostinfo;
    hostname=QHostInfo::localHostName();
    hostinfo=QHostInfo::fromName(hostname);
    ip=hostinfo.addresses();
    return ip;
}

bool XMY_tcpserver::start_server(QHostAddress ip, int port)
{
    bool listen_status=listen(ip,port);
    bool connect_status=db->connect_db();
    if(listen_status && connect_status) {
        return true;
    }
    else if(!connect_status){
        if(db->init_db() && db->connect_db()) return true;
        else if(listen_status) stop_server();
    }
    return false;
}

void XMY_tcpserver::stop_server()
{
    close();
    for(auto i=clients.keyBegin();i!=clients.keyEnd();i++) {
        emit new_log(QString("Disconnecting [%1]:%2 %3").arg(clients[*i]->peerAddress().toString()).arg(clients[*i]->peerPort()).arg(clients[*i]->socketDescriptor()));
        clients[*i]->disconnectFromHost();
    }
    db->disconnect_db();
}


XMY_tcpserver::~XMY_tcpserver()
{
    stop_server();
    delete db;
}

void XMY_tcpserver::incomingConnection(qintptr socketDescriptor)
{
    QUuid socketId=QUuid().createUuid();
    XMY_tcpsocket* socket=new XMY_tcpsocket(socketDescriptor,socketId);
    clients.insert(socketId,socket);
    connect(socket,&XMY_tcpsocket::receive_json,this,&XMY_tcpserver::request_process);
    connect(socket,&XMY_tcpsocket::disconnected,this,&XMY_tcpserver::slot_disconnected);
    emit new_log(QString("New connection from [%1]:%2 %3.").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(socketId.toString()));
}

void XMY_tcpserver::user_authentication(QJsonObject login_info, QJsonObject& ret_data, QUuid socketId)
{
    QString email=login_info.value("email").toString();
    if(!XMY_Utilities::check_valid_email(email)) {
        ret_data.insert("result",LOGIN_INFO_ERROR);
        return;
    }
    QString password=login_info.value("password").toString().toUtf8().toBase64();
    QMap<QString,QVariant> res;
    int result;
    int ret_code=db->get_user_by_email(email, res, "u_password,is_banned,is_waiting_verification");
    if(ret_code==RECORD_NOT_FOUND) result=LOGIN_USER_NOT_FOUND;
    else if(ret_code) result=ret_code;
    else {
        if(res.value("u_password").toString()==password) {
            if(res.value("is_banned").toInt()==1) result=LOGIN_USER_BANNED;
            else if(res.value("is_waiting_verification").toInt()==1) result=LOGIN_USER_WAITING_VERIFICATION;
            else {
                result=LOGIN_SUCCESS;
                if(loginusers.contains(email) && clients.contains(loginusers.value(email))) clients.value(loginusers.value(email))->disconnectFromHost();
                loginusers.insert(login_info.value("email").toString(),socketId);
            }
        }
        else result=LOGIN_INFO_ERROR;
    }
    ret_data.insert("result",result);
}

void XMY_tcpserver::user_create(QJsonObject user_info, QJsonObject& ret_data)
{
    int result;
    QString email=user_info.value("email").toString();
    QString password=user_info.value("password").toString().toUtf8().toBase64();
    QString username=user_info.value("username").toString();
    if(!XMY_Utilities::check_valid_email(email)) {
        ret_data.insert("result",REGISTER_INFO_ERROR);
        return;
    }
    if(db->new_user(email,password,username)) {
        result=REGISTER_WAITING_VERIFICATION;
        send_verification_code(email);
    }
    else result=REGISTER_USER_EXISTED;
    ret_data.insert("result",result);
}

bool XMY_tcpserver::send_message(QString from_email, QString to_email, QString msg)
{
    XMY_tcpsocket* socket=clients.value(loginusers.value(to_email));
    if(socket==NULL) return false;
    QJsonObject data;
    data.insert("type",TYPE_RECEIVE_MESSAGE);
    data.insert("from_email",from_email);
    data.insert("message",msg);
    data.insert("time",XMY_Utilities::get_time_string());
    emit new_log(QJsonDocument(data).toJson(QJsonDocument::Compact));
    socket->send_json(data);
    return true;
}

bool XMY_tcpserver::email_verify(QString email, int code, QJsonObject& ret_data)
{
    QMap<QString,QVariant> info;
    db->get_user_by_email(email, info, "u_verification_code,is_waiting_verification");
    if(info.value("is_waiting_verification").toInt()) {
        if(info.value("u_verification_code").toInt()==code) {
            ret_data.insert("result",REGISTER_SUCCESS);
            db->set_user_by_email(email,"is_waiting_verification",0);
        }
        else {
            ret_data.insert("result",REGISTER_VERIFY_ERROR);
        }
        return true;
    }
    else {
        ret_data.insert("result",REGISTER_SUCCESS);
        return false;
    }
}

void XMY_tcpserver::send_verification_code(QString email)
{
    int code=QRandomGenerator::global()->bounded(10000,99999);
    db->set_user_by_email(email,"is_waiting_verification",1);
    db->set_user_by_email(email,"u_verification_code",code);
    QUrl resource("https://api.mailgun.net/v3/send.emonq.com/messages");
    QNetworkRequest send_request(resource);
    send_request.setRawHeader("Authorization",MAILGUN_KEY);
    send_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkAccessManager* networkmanager = new QNetworkAccessManager();
    connect(networkmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleEndOfRequest(QNetworkReply*)));
    QUrlQuery params;
    params.addQueryItem("from", "xmychat@send.emonq.com");
    params.addQueryItem("to", email);
    params.addQueryItem("html", QString("<p>Your verification code is:</p><h1>%1</h1>").arg(code));
    params.addQueryItem("subject", "XMYChat email verification");
    networkmanager->post(send_request, params.toString().toUtf8());
    emit new_log(QString("Sent verification code %1 to %2").arg(code).arg(email));
}


bool XMY_tcpserver::fetch_friend_list(QString email, QJsonObject& ret)
{
    QMap<QString,QVariant> info;
    if(db->get_user_by_email(email, info, "u_friends")!=SUCCESS) {
        return false;
    }
    QStringList friends=info["u_friends"].toString().split(";", Qt::SkipEmptyParts);
    ret.insert("count",friends.count());
    QJsonArray friends_array;
    for(auto &i:friends) {
        QJsonObject tmp;
        QMap<QString,QVariant> friend_info;
        db->get_user_by_email(i,friend_info,"u_username");
        tmp.insert("email",i);
        tmp.insert("username",friend_info["u_username"].toString());
        QString avatar_file=XMY_Utilities::get_avatar_filename(".avatar\\",i);
        if(!QFile(avatar_file).exists()) avatar_file=".avatar\\default.png";
        tmp.insert("avatarmd5",XMY_Utilities::pixmaptomd5(QPixmap(avatar_file)));
        friends_array.append(tmp);
    }
    ret.insert("list",friends_array);
    return true;
}

void XMY_tcpserver::search_user(QString email, QJsonObject &ret)
{
    QMap<QString, QVariant> info;
    ret.insert("type",TYPE_SEARCH_USER);
    if(db->get_user_by_email(email,info,"u_username")==RECORD_NOT_FOUND) {
        ret.insert("count",0);
        return;
    }
    ret.insert("count",1);
    ret.insert("email",email);
    ret.insert("username",info.value("u_username").toString());
    ret.insert("avatarmd5",XMY_Utilities::pixmaptomd5(QPixmap(XMY_Utilities::get_avatar_filename(".avatar\\",email))));
}

void XMY_tcpserver::add_friend(QString email1, QString email2)
{
    QMap<QString,QVariant> info;
    db->get_user_by_email(email1,info,"u_friends");
    QString friend_list=info.value("u_friends").toString();
    friend_list.append(email2+';');
    db->set_user_by_email(email1,"u_friends",friend_list);
}

void XMY_tcpserver::delete_friend(QString email1, QString email2)
{
    QMap<QString, QVariant> info;
    db->get_user_by_email(email1,info,"u_friends");
    QStringList friend_list=info.value("u_friends").toString().split(';',Qt::SkipEmptyParts);
    friend_list.remove(friend_list.indexOf(email2));
    db->set_user_by_email(email1,"u_friends",friend_list.join(';')+';');
}

void XMY_tcpserver::update_friend_list(QString email)
{
    if(!loginusers.contains(email) || !clients.contains(loginusers.value(email))) return;
    XMY_tcpsocket* socket=clients.value(loginusers.value(email));
    if(socket==NULL) return;
    QJsonObject data;
    data.insert("type",TYPE_FETCH_FRIEND_LIST);
    fetch_friend_list(email,data);
    socket->send_json(data);
}

void XMY_tcpserver::push_update_to_friends(QString email)
{
    QMap<QString,QVariant> info;
    db->get_user_by_email(email,info,"u_friends");
    QStringList friend_list=info.value("u_friends").toString().split(';',Qt::SkipEmptyParts);
    for(auto &i:friend_list) {
        if(loginusers.contains(i) && clients.contains(loginusers.value(i))) update_friend_list(i);
    }
}

void XMY_tcpserver::request_process(QJsonObject req)
{
    QJsonObject ret;
    XMY_tcpsocket* socket=qobject_cast<XMY_tcpsocket*>(sender());
    emit new_log(QString("From [%1]:%2 %3: ").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(socket->socketDescriptor())+QJsonDocument(req).toJson(QJsonDocument::Compact));
    switch(req.value("type").toInt()){
    case TYPE_LOGIN: {
        ret.insert("type",TYPE_LOGIN);
        user_authentication(req,ret,socket->id);
        break;
    }
    case TYPE_REGISTER: {
        ret.insert("type",TYPE_REGISTER);
        user_create(req,ret);
        break;
    }
    case TYPE_LOGOUT: {
        loginusers.remove(req.value("email").toString());
        return;
    }
    case TYPE_SEND_MESSAGE: {
        ret.insert("type",TYPE_SEND_MESSAGE);
        ret.insert("result",send_message(req.value("email").toString(),req.value("to_email").toString(),req.value("message").toString()));
        break;
    }
    case TYPE_VERIFY: {
        ret.insert("type",TYPE_REGISTER);
        email_verify(req.value("email").toString(),req.value("code").toInt(),ret);
        break;
    }
    case TYPE_INFO_MODIFY: {
        QString email=req.value("email").toString();
        for(auto &i:req.keys()) {
            if(i=="avatar") XMY_Utilities::save_pic_from_base64(req.value(i).toString(),".avatar\\"+XMY_Utilities::emailtomd5(email)+".png");
            else if(i=="email") {
                if(XMY_Utilities::check_valid_email(req.value(i).toString()))
                    db->set_user_by_email(email,"u_email",req.value(i).toString());
            }
            else if(i=="username") db->set_user_by_email(email,"u_username",req.value(i));
            else if(i=="password") db->set_user_by_email(email,"u_password",req.value(i).toString().toUtf8().toBase64());
        }
        push_update_to_friends(email);
        break;
    }
    case TYPE_GET_USER_INFO: {
        QMap<QString,QVariant> info;
        db->get_user_by_email(req.value("email").toString(),info,"u_username");;
        ret.insert("type",TYPE_GET_USER_INFO);
        ret.insert("username",info.value("u_username").toString());
        break;
    }
    case TYPE_GET_AVATAR: {
        XMY_Utilities::checkDir(".avatar");
        QString filename=".avatar\\"+XMY_Utilities::emailtomd5(req.value("email").toString())+".png";
        if(!QFile(filename).exists()) filename=".avatar\\default.png";
        ret.insert("type",TYPE_GET_AVATAR);
        ret.insert("email",req.value("email").toString());
        if(XMY_Utilities::pixmaptomd5(QPixmap(filename))==req.value("md5").toString()) {
            ret.insert("result",GET_AVATAR_NOCHANGE);
        }
        else {
            ret.insert("result",GET_AVATAR_OK);
            ret.insert("avatar",XMY_Utilities::get_pic_base64(filename));
        }
        break;
    }
    case TYPE_FETCH_FRIEND_LIST: {
        ret.insert("type",TYPE_FETCH_FRIEND_LIST);
        fetch_friend_list(req.value("email").toString(),ret);
        break;
    }
    case TYPE_SEARCH_USER: {
        search_user(req.value("email").toString(),ret);
        break;
    }
    case TYPE_ADD_FRIEND: {
        add_friend(req.value("email1").toString(),req.value("email2").toString());
        add_friend(req.value("email2").toString(),req.value("email1").toString());
        update_friend_list(req.value("email1").toString());
        update_friend_list(req.value("email2").toString());
        break;
    }
    case TYPE_DELETE_FRIEND: {
        delete_friend(req.value("email1").toString(),req.value("email2").toString());
        delete_friend(req.value("email2").toString(),req.value("email1").toString());
        update_friend_list(req.value("email1").toString());
        update_friend_list(req.value("email2").toString());
        break;
    }
    default: {
        return;
    }
    }
    emit new_log(QString("To [%1]:%2 %3: ").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(socket->socketDescriptor())+QJsonDocument(ret).toJson(QJsonDocument::Compact));
    socket->send_json(ret);
}

void XMY_tcpserver::handleEndOfRequest(QNetworkReply *reply)
{
    emit new_log(reply->readAll());
    QNetworkAccessManager* manager=qobject_cast<QNetworkAccessManager*>(sender());
    manager->deleteLater();
}

void XMY_tcpserver::slot_disconnected()
{
    XMY_tcpsocket* client=qobject_cast<XMY_tcpsocket*>(sender());
    emit new_log(QString("[%1]:%2 %3 disconnected.").arg(client->peerAddress().toString()).arg(client->peerPort()).arg(client->id.toString()));
    clients.remove(client->id);
    client->deleteLater();
}
