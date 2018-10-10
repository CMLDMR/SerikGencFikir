#ifndef BODY_H
#define BODY_H

#include "baseclass.h"

namespace Body {



class Body : public BaseWidget
{
public:
    Body(mongocxx::database* _db);

    void initMainPage();

    void gencFikirInit();

    void BasvuruInit();


private:
    WContainerWidget* mMainContainer;

};
}




#endif // BODY_H
