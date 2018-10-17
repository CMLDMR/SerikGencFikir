#ifndef DAVETIYEWIDGET_H
#define DAVETIYEWIDGET_H

#include <QtCore/qglobal.h>

#include "baseclass.h"
#include "user.h"

using namespace Wt;

class DavetiyeWidget : public BaseWidget , public User
{
public:
    DavetiyeWidget(mongocxx::database* _db , bsoncxx::document::view userDocument);

private:
//    User* mUser;


    WContainerWidget* mRow;
    WContainerWidget* mContainer;

    void initDavetiler();
};

#endif // DAVETIYEWIDGET_H
