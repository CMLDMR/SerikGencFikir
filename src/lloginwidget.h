#ifndef LLOGINWIDGET_H
#define LLOGINWIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>





#include <Wt/WLineEdit.h>
#include <Wt/WComboBox.h>

#include "baseclass.h"

using namespace Wt;

class LLoginWidget : public BaseWidget
{
public:
    LLoginWidget(mongocxx::database* _db);

    ~LLoginWidget(){}


    void initLoginPage();

    void inityeniUye();

    void Login();

    WContainerWidget* mMainContainer,*row;
    WLineEdit* mTel;
    WLineEdit* mSifre;


    Signal<bsoncxx::document::view> &Logined();

private:
    Signal<bsoncxx::document::view> _Logined;
};




class LYeniUye : public BaseWidget
{
public:
    LYeniUye(mongocxx::database* _db);

    Signal<NoClass> &LoginSuccess();

private:
    WContainerWidget* mRow;

    void sendVericationCode();

    std::string verificationCode;

    WPushButton* mKaydet;
    WLineEdit* mCepTel;
    WLineEdit* mAdres;
    WLineEdit* mTCNO;
    WLineEdit* mAdSoyad;
    WComboBox* mUniversite;
    WLineEdit* mSifre;

    WLineEdit* mDogrulamaKodu;

//    WLineEdit* dogrulamaKodu;
    void SaveNewUser();

    Signal<NoClass> _LoginSuccess;
};



#endif // LLOGINWIDGET_H
