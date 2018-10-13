#include "lloginwidget.h"
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WDialog.h>
#include <Wt/WIntValidator.h>


#include "user.h"

LLoginWidget::LLoginWidget(mongocxx::database *_db)
    :BaseWidget (_db)
{
    //    addWidget(cpp14::make_unique<WText>("ŞLPĞİŞÜÇÖç"));

    setContentAlignment(AlignmentFlag::Center);
    setMaximumSize(1024,WLength::Auto);

    mMainContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    mMainContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    row = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    row->addStyleClass(Bootstrap::Grid::row);

    this->initLoginPage();

}

void LLoginWidget::initLoginPage()
{
    row->clear();



    auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());

    container->addStyleClass(Bootstrap::Grid::col_full_12);
    container->setContentAlignment(AlignmentFlag::Center);


    auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());

    mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    mContainer->setMaximumSize(650,WLength::Auto);

    mContainer->setMargin(200,Side::Top|Side::Bottom);

    mContainer->addStyleClass("loginLoginContainer");


    auto mRow = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());

    mRow->addStyleClass(Bootstrap::Grid::row);
    mRow->setContentAlignment(AlignmentFlag::Center);
    mRow->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0,0.25));

    {
        auto textContainer = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        textContainer->addStyleClass(Bootstrap::Grid::col_full_12);
        textContainer->setHeight(300);

        auto vLayout = textContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

        vLayout->addStretch(1);

        {
            mTel = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center);
            mTel->setPlaceholderText("Telefon Numarasını Giriniz");

        }

        {
            mSifre = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center);
            mSifre->setPlaceholderText(WString::fromUTF8("Şifrenizi Giriniz"));
            mSifre->setEchoMode(EchoMode::Password);
        }

        {
            auto giris = vLayout->addWidget(cpp14::make_unique<WPushButton>(WString::fromUTF8("Giriş")),0,AlignmentFlag::Center);
            giris->addStyleClass(Bootstrap::Button::Primary);
            giris->clicked().connect(this,&LLoginWidget::Login);
        }

        {
            auto unuttum = vLayout->addWidget(cpp14::make_unique<WPushButton>("Şifremi Unuttum"),0,AlignmentFlag::Center);
            unuttum->addStyleClass(Bootstrap::Button::Success);
        }

        {
            auto uye = vLayout->addWidget(cpp14::make_unique<WPushButton>("Yeni Üye Ol"),0,AlignmentFlag::Center);
            uye->addStyleClass(Bootstrap::Button::Warning);
            uye->clicked().connect(this,&LLoginWidget::inityeniUye);
        }
        vLayout->addStretch(1);
    }

}

void LLoginWidget::inityeniUye()
{
    row->clear();

    auto newUye = row->addWidget(cpp14::make_unique<LYeniUye>(this->getDb()));
    newUye->addStyleClass(Bootstrap::Grid::col_full_12);

    newUye->LoginSuccess().connect([=](){

        this->initLoginPage();

    });
}

void LLoginWidget::Login()
{

    auto filter = document{};

    try {
        filter.append(kvp("ceptelkey",mTel->text().toUTF8().c_str()));
    } catch (bsoncxx::exception &e) {
        std::cout << "Can Not Capture ceptelkey" << std::endl;
    }

    try {
        filter.append(kvp("passwordkey",mSifre->text().toUTF8().c_str()));
    } catch (bsoncxx::exception &e) {
        std::cout << "Can Not Capture passwordkey" << std::endl;
    }

    try {
        auto val = this->collection("Users").find_one(filter.view());

        if( val )
        {
            auto view = val.value().view();

            _Logined.emit(view);
        }else{
            std::cout << "No Returned Value " << std::endl;
        }

    } catch (mongocxx::exception &e) {
        std::cout << "login mongocxx Error: " << e.what() << std::endl;
    }


}

Signal<bsoncxx::document::view> &LLoginWidget::Logined()
{
    return _Logined;
}

LYeniUye::LYeniUye(mongocxx::database *_db)
    :BaseWidget (_db)
{

    addStyleClass(Bootstrap::Grid::container_fluid);

    this->mRow = addWidget(cpp14::make_unique<WContainerWidget>());
    this->mRow->addStyleClass(Bootstrap::Grid::row);


    const int inputWidth = 400;

    {
        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setMargin(10,Side::Top|Side::Bottom);

        auto text = container->addWidget(cpp14::make_unique<WText>("Üye Ol"));
        text->setAttributeValue(Style::style,Style::font::size::s24px+Style::color::color(Style::color::White::AliceBlue));
    }



    {

        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        row->addStyleClass(Bootstrap::Grid::row);

        auto tContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        tContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);

        mAdSoyad = tContainer->addWidget(cpp14::make_unique<WLineEdit>());
        mAdSoyad->setMaximumSize(inputWidth,WLength::Auto);
        mAdSoyad->setMargin(WLength::Auto,AllSides);
        mAdSoyad->setPlaceholderText("Adınızı Soyadınızı Yazınız");

    }

    {

        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        row->addStyleClass(Bootstrap::Grid::row);

        auto tContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        tContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);

        mTCNO = tContainer->addWidget(cpp14::make_unique<WLineEdit>());
        mTCNO->setMaximumSize(inputWidth,WLength::Auto);
        mTCNO->setMargin(WLength::Auto,AllSides);
        mTCNO->setPlaceholderText("TCNO Yazınız");

    }

    {

        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        row->addStyleClass(Bootstrap::Grid::row);

        auto tContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        tContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);

        mCepTel = tContainer->addWidget(cpp14::make_unique<WLineEdit>());
        mCepTel->setMaximumSize(inputWidth,WLength::Auto);
        mCepTel->setMargin(WLength::Auto,AllSides);
        mCepTel->setPlaceholderText("Cep Telefonunuzu Yazınız");

    }

    {

        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        row->addStyleClass(Bootstrap::Grid::row);

        auto tContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        tContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);

        mAdres = tContainer->addWidget(cpp14::make_unique<WLineEdit>());
        mAdres->setMaximumSize(inputWidth,WLength::Auto);
        mAdres->setMargin(WLength::Auto,AllSides);
        mAdres->setPlaceholderText("Adres Giriniz");

    }

    {

        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        row->addStyleClass(Bootstrap::Grid::row);

        auto tContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        tContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
        tContainer->setContentAlignment(AlignmentFlag::Center);

        mUniversite = tContainer->addWidget(cpp14::make_unique<WComboBox>());
        mUniversite->setMaximumSize(inputWidth,WLength::Auto);
        mUniversite->setMargin(WLength::Auto,AllSides);
        mUniversite->addItem("Üniversite Seçiniz");

        mUniversite->addItem("AKEV Üniversitesi");
        mUniversite->addItem("Akdeniz Üniversitesi - Fakülte");
        mUniversite->addItem("Akdeniz Üniversitesi - Yüksek Okul");
    }

    {

        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        row->addStyleClass(Bootstrap::Grid::row);

        auto tContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
        tContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);

        mSifre = tContainer->addWidget(cpp14::make_unique<WLineEdit>());
        mSifre->setMaximumSize(inputWidth,WLength::Auto);
        mSifre->setMargin(WLength::Auto,AllSides);
        mSifre->setPlaceholderText("Şifrenizi Giriniz ( en az 6 haneli )");

    }

    {
        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto mContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        mContainer->addStyleClass(Bootstrap::Grid::container_fluid);
        mContainer->setMaximumSize(inputWidth,WLength::Auto);

        auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        row->addStyleClass(Bootstrap::Grid::row);

        {
            auto tContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
            tContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);
            tContainer->setContentAlignment(AlignmentFlag::Center);
            auto gonder = tContainer->addWidget(cpp14::make_unique<WPushButton>("Kodu Gönder"));

            gonder->clicked().connect([&](){
                this->sendVericationCode();
            });
        }

        {
            auto tContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
            tContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);
            tContainer->setContentAlignment(AlignmentFlag::Center);
            mDogrulamaKodu = tContainer->addWidget(cpp14::make_unique<WLineEdit>());
            mDogrulamaKodu->setPlaceholderText("Doğrulama Kodunu Giriniz");

        }




    }


    {
        auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setMargin(25,Side::Top|Side::Bottom);

        mKaydet = container->addWidget(cpp14::make_unique<WPushButton>("Kaydet"));
        mKaydet->addStyleClass(Bootstrap::Button::Primary);
        mKaydet->setEnabled(false);
        mKaydet->clicked().connect(this,&LYeniUye::SaveNewUser);

        mDogrulamaKodu->textInput().connect([=](){

            if( mDogrulamaKodu->text().toUTF8().size() == 4 )
            {

                if( verificationCode == mDogrulamaKodu->text().toUTF8() )
                {
                    mKaydet->setEnabled(true);
                }
            }else{
                mKaydet->setEnabled(false);
            }

        });
    }



}

Signal<NoClass> &LYeniUye::LoginSuccess()
{

    return _LoginSuccess;

}

void LYeniUye::sendVericationCode()
{

    if( this->mAdSoyad->text().empty() )
    {
        this->ShowMessage("Ad Soyad Girmediniz");
        return;
    }

    if( this->mTCNO->text().empty() )
    {
        this->ShowMessage("TCNO Girmediniz");
        return;
    }

    if( this->mCepTel->text().toUTF8().size() != 11 )
    {
        this->ShowMessage("Cep Telefonu Girmediniz. Numaranın Başında 0 Kullanarak Giriniz");
        return;
    }

    if( this->mAdres->text().toUTF8().size() == 0 )
    {
        this->ShowMessage("Adres Girmediniz");
        return;
    }

    if( this->mSifre->text().toUTF8().size() < 6 )
    {
        this->ShowMessage("Şireniz En Az 6 Karakter Olmalı");
        return;
    }

    if( this->mUniversite->currentIndex() == 0 )
    {
        this->ShowMessage("Üniversite Seçmediniz");
        return;
    }

    std::uniform_int_distribution<int> d(1000, 9999);
    std::random_device rd1;
    verificationCode = std::to_string(d(rd1));

    std::string sms = std::string("SerikGencFikir, Doğrulama Kodu: ") + verificationCode.c_str() + std::string(" .Bu İsteği Siz Bulunmadıysanız Dikkate Almayınız");

    this->sendSMS(this->mCepTel->text().toUTF8().c_str(),sms);


    mKaydet->setEnabled(false);

}

void LYeniUye::SaveNewUser()
{

    std::cout << "Save new User" << std::endl;


    std::unique_ptr<User> usrPtr = std::make_unique<User>();

    User* user = usrPtr.get();

    user->setAddres(mAdres->text().toUTF8());
    user->setAdsoyad(mAdSoyad->text().toUTF8());
    user->setPassword(mSifre->text().toUTF8());
    user->setTcno(mTCNO->text().toUTF8());
    user->setCeptel(mCepTel->text().toUTF8());
    user->setUniversite(mUniversite->currentText().toUTF8());

    try {
        auto val = this->collection("Users").insert_one(user->getDocument().view());

        if( val.value().result().inserted_count() )
        {
            _LoginSuccess.emit(NoClass());
        }
    } catch (mongocxx::exception &e) {
        std::cout << "User insert one: " << e.what() << std::endl;
    }


}
