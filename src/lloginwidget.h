#ifndef LLOGINWIDGET_H
#define LLOGINWIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include "bootstrap.h"
#include "inlinestyle.h"


#include <Wt/WLineEdit.h>


using namespace Wt;

class LLoginWidget : public Wt::WContainerWidget
{
public:
    LLoginWidget();

    ~LLoginWidget(){}


    void initLoginPage();

    void inityeniUye();


    WContainerWidget* mMainContainer,*row;
    WLineEdit* mTel;
};




class LYeniUye : public WContainerWidget
{
public:
    LYeniUye();
};



#endif // LLOGINWIDGET_H
