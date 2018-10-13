#include "userwidget.h"

#include <Wt/WImage.h>
#include <Wt/WFileUpload.h>
#include <Wt/WProgressBar.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>


UserWidget::UserWidget(mongocxx::database *_db, User *_user)
    :BaseWidget (_db),User (_user)
{
    this->initPage();
}

UserWidget::UserWidget(mongocxx::database *_db, bsoncxx::document::view userView)
    :BaseWidget (_db),User (userView)
{
    this->initPage();
}

void UserWidget::initPage()
{

    setMargin(25,Side::Top);

    mMainContainer = addWidget(cpp14::make_unique<WContainerWidget>());

    mMainContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    mRow = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());

    mRow->addStyleClass(Bootstrap::Grid::row);

    infoContainer = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
    infoContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_3+Bootstrap::Grid::ExtraSmall::col_xs_12);
    infoContainer->setAttributeValue(Style::style,Style::Border::border("2px solid white")+
                                     Style::Border::borderRardius("25","5","25","5")+
                                     Style::background::color::rgba(0,0,0,.25));

    contentContainer = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
    contentContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_9+Bootstrap::Grid::Medium::col_md_9+Bootstrap::Grid::Small::col_sm_9+Bootstrap::Grid::ExtraSmall::col_xs_12);
    contentContainer->setAttributeValue(Style::style,Style::Border::border("2px solid white")+
                                     Style::Border::borderRardius("5","25","5","25")+
                                     Style::background::color::rgba(0,0,0,.25));

    this->initInfo();

    this->initContent();


}

void UserWidget::initInfo()
{

    infoContainer->clear();

    auto fContainer = infoContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    fContainer->setMargin(10,AllSides);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);



    auto photoContainer = rContainer->addWidget( cpp14::make_unique<WContainerWidget>() );
    photoContainer->addStyleClass( Bootstrap::Grid::col_full_12 );
    photoContainer->setContentAlignment( AlignmentFlag::Center );
    auto photo = photoContainer->addWidget( cpp14::make_unique<WContainerWidget>() );

    bool fotoexist = false;
    std::string fotourl = "icon/person.png";

    if( this->getFotoid().size() )
    {
        std::cout << "Download File : " << this->getFotoOid().to_string() << std::endl;

        fotourl = this->download(this->getFotoOid());

        std::cout << "FOTO URL : " << fotourl << std::endl;
    }


//    try {


//    } catch (mongocxx::exception &e) {
//        this->ShowMessage(std::string("Hata: ") + e.what() );
//        fotoexist = false;
//    }

    photo->setAttributeValue( Style::style , Style::background::url(fotourl) +
                              Style::background::size::contain +
                              Style::background::repeat::norepeat +
                              Style::background::position::center_center);
    photo->setHeight( 160 );


    auto uploadController = photoContainer->addWidget(cpp14::make_unique<WContainerWidget>());

    {

        Wt::WFileUpload *fu = uploadController->addWidget(Wt::cpp14::make_unique<Wt::WFileUpload>());

        fu->setProgressBar(Wt::cpp14::make_unique<Wt::WProgressBar>());


        Wt::WText *out = rContainer->addWidget(Wt::cpp14::make_unique<Wt::WText>());



        fu->changed().connect([=] {
            fu->upload();
            out->setText("Yükleniyor...");
        });



        fu->uploaded().connect([=] {
            if( fu->uploadedFiles().size() )
            {
                out->setText("Yükleme Tamamlandı");
                for( auto item : fu->uploadedFiles() )
                {
                    std::string nameFilename = std::string("docroot/temp/")+item.clientFileName().c_str();
                    std::cout << "File Renamed: " << QFile::rename(item.spoolFileName().c_str(), nameFilename.c_str() ) << std::endl;

                    auto fotoid = this->uploadfile(nameFilename.c_str());

                    auto filter = document{};

                    try {
                        filter.append(kvp("tcnokey",this->getTcno()));
                    } catch (bsoncxx::exception &e) {
                        this->ShowMessage(std::string("Hata tcno: ")+e.what());
                        return;
                    }

                    auto setDoc = document{};

                    try {
                        setDoc.append(kvp("$set",make_document(kvp("foto",fotoid.get_oid()))));
                    } catch (bsoncxx::exception &e) {
                        this->ShowMessage(std::string("Hata fotooid: ")+e.what());
                        return;
                    }

                    try {

                        auto upt = this->getDb()->collection("Users").update_one(filter.view(),setDoc.view());

                        if( upt )
                        {
                            if( upt.value().modified_count() )
                            {
                                this->setFotoid(fotoid.get_oid().value.to_string());
                                this->initInfo();
                            }
                        }

                    } catch (mongocxx::exception &e) {
                        this->ShowMessage(std::string("Hata update: ")+e.what());
                        return;
                    }


                }
            }
        });

        // React to a file upload problem.
        fu->fileTooLarge().connect([=] {
            out->setText("Dosya Fazla Büyük Dosya Boyutunu Düşürün");
        });

    }


//    auto uploadBtn = photoContainer->addWidget(cpp14::make_unique<WPushButton>("Resim Yükle"));






    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(15,Side::Top|Side::Bottom);
        container->addStyleClass( Bootstrap::Grid::col_full_12 );
        auto text = container->addWidget(cpp14::make_unique<WText>(this->getAdsoyad()));
        text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
    }


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(15,Side::Top|Side::Bottom);
        container->addStyleClass( Bootstrap::Grid::col_full_12 );
        auto text = container->addWidget(cpp14::make_unique<WText>(this->getCeptel()));
        text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(15,Side::Top|Side::Bottom);
        container->addStyleClass( Bootstrap::Grid::col_full_12 );
        auto text = container->addWidget(cpp14::make_unique<WText>(this->getTcno()));
        text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(15,Side::Top|Side::Bottom);
        container->addStyleClass( Bootstrap::Grid::col_full_12 );
        auto text = container->addWidget(cpp14::make_unique<WText>(this->getUniversite()));
        text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
    }
}

void UserWidget::initContent()
{

    contentContainer->clear();

    mProject = contentContainer->addWidget(cpp14::make_unique<Project>(this->getDb(),this->getUser()));

}

