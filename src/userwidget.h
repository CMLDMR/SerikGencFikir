#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QtCore/qglobal.h>
#include "baseclass.h"
#include "user.h"
#include "project.h"
#include "davetiyewidget.h"

class UserWidget : public BaseWidget , public User
{
public:
    UserWidget(mongocxx::database* _db , User* _user);
    UserWidget(mongocxx::database* _db , bsoncxx::document::view userView);


    void initPage();

    void initInfo();

    void initContent();

    void initDavetiyeler();

    Signal<NoClass> &LogOut();

private:
    WContainerWidget* mMainContainer, *mRow;

    WContainerWidget* infoContainer;
    WContainerWidget* contentContainer;
    WContainerWidget* davetiyeContainer;

    Project* mProject;

    DavetiyeWidget* mDavetiyeWidget;

    Signal<NoClass> _logOut;

};

#endif // USERWIDGET_H
