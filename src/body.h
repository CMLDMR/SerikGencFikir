#ifndef BODY_H
#define BODY_H

#include <Wt/WContainerWidget.h>

#include "inlinestyle.h"
#include "bootstrap.h"

using namespace Wt;



namespace Body {
class Body : public WContainerWidget
{
public:
    Body();

    void initMainPage();

    void gencFikirInit();


private:
    WContainerWidget* mMainContainer;
};
}




#endif // BODY_H
