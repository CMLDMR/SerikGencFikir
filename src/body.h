#ifndef BODY_H
#define BODY_H

#include "baseclass.h"
#include "user.h"

namespace Body {



class Body : public BaseWidget
{
public:
    Body(mongocxx::database* _db);

    void initMainPage();

    void gencFikirInit();

    void BasvuruInit();

    void Sartnameinit();

    void ProjeFormat();


    void initUserWidget(bsoncxx::document::view view);


private:
    WContainerWidget* mMainContainer;


    bool _Logined;
    User userInfo;

};
}




#endif // BODY_H
