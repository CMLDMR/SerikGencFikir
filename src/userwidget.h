#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QtCore/qglobal.h>
#include "baseclass.h"
#include "user.h"
#include "project.h"

class UserWidget : public BaseWidget , public User
{
public:
    UserWidget(mongocxx::database* _db , User* _user);
    UserWidget(mongocxx::database* _db , bsoncxx::document::view userView);


    void initPage();

    void initInfo();

    void initContent();

private:
    WContainerWidget* mMainContainer, *mRow;

    WContainerWidget* infoContainer;
    WContainerWidget* contentContainer;

    Project* mProject;

};

#endif // USERWIDGET_H
