#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H


#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include "bootstrap.h"
#include "inlinestyle.h"


using namespace Wt;


namespace Login {
class LoginWidget : public WContainerWidget
{
public:
    LoginWidget();
    ~LoginWidget(){}

    void initLoginPage();

//    void inityeniUye();

    WContainerWidget* mMainContainer;

};
}



//class YeniUyelik : public WContainerWidget
//{
//public:
//    YeniUyelik();

//};

#endif // LOGINWIDGET_H
