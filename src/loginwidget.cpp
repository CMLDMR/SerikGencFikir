#include "loginwidget.h"
//#include <Wt/WVBoxLayout.h>
//#include <Wt/WHBoxLayout.h>
//#include <Wt/WLineEdit.h>
//#include <Wt/WPushButton.h>
//#include <Wt/WString.h>


Login::LoginWidget::LoginWidget()
{

    setContentAlignment(AlignmentFlag::Center);

    mMainContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    mMainContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    auto row = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    row->addStyleClass(Bootstrap::Grid::row);

    auto text = row->addWidget(cpp14::make_unique<WText>("ŞŞĞĞİİÖÖÇÇ"));

}




void Login::LoginWidget::initLoginPage()
{

//    row->clear();



//    auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());

//    container->addStyleClass(Bootstrap::Grid::col_full_12);
//    container->setContentAlignment(AlignmentFlag::Center);


//    auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());

//    mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

//    mContainer->setMaximumSize(650,WLength::Auto);

//    mContainer->setMargin(200,Side::Top|Side::Bottom);

//    mContainer->addStyleClass("loginLoginContainer");


//    auto mRow = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());

//    mRow->addStyleClass(Bootstrap::Grid::row);
//    mRow->setContentAlignment(AlignmentFlag::Center);
//    mRow->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0,0.25));

//    {
//        auto textContainer = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
//        textContainer->addStyleClass(Bootstrap::Grid::col_full_12);
//        textContainer->setHeight(300);

//        auto vLayout = textContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

//        vLayout->addStretch(1);

//        {
//            auto container_ = textContainer->addWidget(cpp14::make_unique<WContainerWidget>());
//            auto tel = container_->addWidget(cpp14::make_unique<WLineEdit>());
////            tel->setPlaceholderText("Telefon Numarası Giriniz");
//        }

//        {
////            mTel = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center);
////            mTel->setPlaceholderText("Telefon Numarasını Giriniz");

//            auto container_ = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
//            auto hlayout = container_->setLayout(cpp14::make_unique<WHBoxLayout>());

//            auto teltext = hlayout->addWidget(cpp14::make_unique<WText>(WString::fromUTF8("Telefon Numarasi")),0,AlignmentFlag::Right);
//            auto tel = hlayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Left);
//        }

//        {
//            auto sifre = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center);
////            sifre->setPlaceholderText(WString::fromUTF8("Sifrenizi Giriniz"));
//            sifre->setEchoMode(EchoMode::Password);
//        }

//        {
//            auto giris = vLayout->addWidget(cpp14::make_unique<WPushButton>(WString::fromUTF8("Giriş")),0,AlignmentFlag::Center);
//            giris->addStyleClass(Bootstrap::Button::Primary);
//        }

//        {
//            auto unuttum = vLayout->addWidget(cpp14::make_unique<WPushButton>("Şifremi Unuttum"),0,AlignmentFlag::Center);
//            unuttum->addStyleClass(Bootstrap::Button::Success);
//        }

//        {
//            auto uye = vLayout->addWidget(cpp14::make_unique<WPushButton>("Yeni Üye Ol"),0,AlignmentFlag::Center);
//            uye->addStyleClass(Bootstrap::Button::Warning);
//            uye->clicked().connect(this,&LoginWidget::inityeniUye);
//        }
//        vLayout->addStretch(1);
//    }

}

//void Login::LoginWidget::inityeniUye()
//{

////    row->clear();

////    auto yeniuye = row->addWidget(cpp14::make_unique<YeniUyelik>());


////    yeniuye->addStyleClass(Bootstrap::Grid::col_full_12);

//}

