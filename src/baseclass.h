#ifndef BASECLASS_H
#define BASECLASS_H

#include <QtCore/qglobal.h>

#include "mongocxx/database.hpp"
#include "inlinestyle.h"
#include "bootstrap.h"


#include <random>

#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

using namespace Wt;

class BaseClass
{
public:
    BaseClass(mongocxx::database* _db);





    mongocxx::database *getDb();

private:
    mongocxx::database* db;
};





class BaseWidget : public WContainerWidget , public BaseClass
{
public:
    BaseWidget(mongocxx::database* _db);

    void sendSMS(std::string numara , std::string sms);


    enum class MessageType{
        info = 0 ,
        warning
    };

    void ShowMessage(std::string mesaj , MessageType type = MessageType::info );



};



#endif // BASECLASS_H
