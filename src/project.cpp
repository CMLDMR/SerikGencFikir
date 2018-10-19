#include "project.h"
#include <Wt/WHBoxLayout.h>
#include <Wt/WComboBox.h>
#include <Wt/WFileUpload.h>
#include <Wt/WProgressBar.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WBreak.h>

Project::Project(mongocxx::database *_db, User user)
    :BaseWidget (_db) , User (user)
{

    setId("ProjectWidget");
    addStyleClass(Bootstrap::Grid::container_fluid);

    auto row = addWidget(cpp14::make_unique<WContainerWidget>());
    row->addStyleClass(Bootstrap::Grid::row);

    mTitleContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
    mTitleContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    initTitleContainer();


    mListContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
    mListContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    this->initProjectList();

    mController = row->addWidget(cpp14::make_unique<WContainerWidget>());
    mController->addStyleClass(Bootstrap::Grid::col_full_12);

    this->initController();

    mNewContainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
    mNewContainer->addStyleClass(Bootstrap::Grid::col_full_12);


}

void Project::initTitleContainer()
{


    auto contentContainer = mTitleContainer->addWidget(cpp14::make_unique<WContainerWidget>());


    auto filter = document{};



    try {
        filter.append(kvp("tcno",this->getTcno()));
    } catch (bsoncxx::exception &e) {
        std::cout << "Filter Error: " << e.what() << std::endl;
    }


    try {

        auto count = this->getDb()->collection("Projeler").count(filter.view());

        auto fContainer = contentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        fContainer->addStyleClass(Bootstrap::Grid::container_fluid);
        fContainer->setMargin(10,Side::Bottom|Side::Top);

        auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        rContainer->addStyleClass(Bootstrap::Grid::row);

        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);
        auto text = container->addWidget(cpp14::make_unique<WText>(std::string("Yüklenen Proje Sayısı: ") + std::to_string(count)));
        text->setAttributeValue(Style::style,Style::font::size::s18px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::lighter);

    } catch (mongocxx::exception &e) {
        auto fContainer = contentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        fContainer->addStyleClass(Bootstrap::Grid::container_fluid);

        auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        rContainer->addStyleClass(Bootstrap::Grid::row);

        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);
        auto text = container->addWidget(cpp14::make_unique<WText>(std::string("Hata: ")+e.what()));
        text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);

    }

}

void Project::initProjectList()
{


    mListContainer->clear();


    auto filter = document{};

    try {
        filter.append(kvp("tcno",this->getTcno()));
    } catch (bsoncxx::exception &e) {
        this->ShowMessage(std::string("Hata: ") + e.what());
        return;
    }

    try {

        auto cursor = this->getDb()->collection("Projeler").find(filter.view());

        for( auto doc : cursor )
        {

            auto contentContainer = mListContainer->addWidget(cpp14::make_unique<WContainerWidget>());

            auto fContainer = contentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            fContainer->addStyleClass(Bootstrap::Grid::container_fluid);
            fContainer->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0));
            fContainer->setMargin(5,Side::Top);


            auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            rContainer->addStyleClass(Bootstrap::Grid::row);

            {
                auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+
                                         Bootstrap::Grid::Medium::col_md_6+
                                         Bootstrap::Grid::Small::col_sm_12+
                                         Bootstrap::Grid::ExtraSmall::col_xs_6);
                container->setContentAlignment(AlignmentFlag::Center);

                auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                {
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(doc["projeadi"].get_utf8().value.to_string()),
                            0,
                            AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::lighter);
                    text->setMargin(WLength::Auto,AllSides);
                }
            }

            {
                auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+
                                         Bootstrap::Grid::Medium::col_md_2+
                                         Bootstrap::Grid::Small::col_sm_6+
                                         Bootstrap::Grid::ExtraSmall::col_xs_6);
                container->setContentAlignment(AlignmentFlag::Center);
                container->setAttributeValue(Style::style,Style::Border::left::border("1px solid white"));

                auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                {
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(std::string("Kategori")),
                                                   0,
                                                   AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                    text->setMargin(WLength::Auto,AllSides);
                }

                {
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(doc["projeKategori"].get_utf8().value.to_string()),
                            0,
                            AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::lighter);
                    text->setMargin(WLength::Auto,AllSides);
                }
            }

            {
                auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_1+
                                         Bootstrap::Grid::Medium::col_md_1+
                                         Bootstrap::Grid::Small::col_sm_2+
                                         Bootstrap::Grid::ExtraSmall::col_xs_3);
                container->setContentAlignment(AlignmentFlag::Center);
                container->setHeight(75);
                container->setAttributeValue(Style::style,Style::background::color::rgba(127,0,0));

                auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                {
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(std::string("Sil")),
                                                   0,
                                                   AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                    text->setMargin(WLength::Auto,AllSides);
                }

                container->decorationStyle().setCursor(Cursor::PointingHand);

                container->setAttributeValue(Style::dataoid,doc["_id"].get_oid().value.to_string());

                container->clicked().connect([=](){
                    auto mDialog = this->addChild(cpp14::make_unique<WDialog>("Sil?"));


                    Wt::WLabel *label =
                            mDialog->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLabel>("Silmek İstediğinize Eminmisiniz?"));


                    Wt::WPushButton *ok =
                            mDialog->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Evet"));
                    ok->setDefault(true);

                    Wt::WPushButton *cancel =
                            mDialog->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Hayır"));
                    mDialog->rejectWhenEscapePressed();


                    ok->clicked().connect([=] {
                        mDialog->accept();
                    });

                    cancel->clicked().connect(mDialog, &Wt::WDialog::reject);

                    mDialog->finished().connect([=] {
                        if (mDialog->result() == Wt::DialogCode::Accepted)
                        {
                            if( this->deleteProject(container->attributeValue(Style::dataoid).toUTF8()) ){

                                this->initProjectList();

                            }

                        }else{
                            this->removeChild(mDialog);
                        }
                    });

                    mDialog->show();
                });

            }

            {
                auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+
                                         Bootstrap::Grid::Medium::col_md_3+
                                         Bootstrap::Grid::Small::col_sm_4+
                                         Bootstrap::Grid::ExtraSmall::col_xs_6);
                container->setContentAlignment(AlignmentFlag::Center);
                container->setHeight(75);
                container->setAttributeValue(Style::style,Style::background::color::rgba(0,127,0));

                auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                container->setAttributeValue(Style::dataoid,doc["dosya"].get_oid().value.to_string());

                auto downloadlink = this->downloadProjectFile(container->attributeValue(Style::dataoid).toUTF8());

                std::cout << "Download Link: " << downloadlink << std::endl;

                QFileInfo info( doc["dosyaadi"].get_utf8().value.to_string().c_str());

                QString newFileName = QString("docroot/tempfile/")+container->attributeValue(Style::dataoid).toUTF8().c_str() + "." +info.suffix().toStdString().c_str();

                QString downloadFileName = QString("tempfile/")+container->attributeValue(Style::dataoid).toUTF8().c_str() + "." +info.suffix().toStdString().c_str();

                std::cout << "File Renamed: " << QFile::rename(QString("docroot/")+downloadlink.c_str(),newFileName) << std::endl;


                Wt::WLink link = Wt::WLink(downloadFileName.toStdString());
                link.setTarget(Wt::LinkTarget::NewWindow);

                std::unique_ptr<Wt::WAnchor> anchor =
                        Wt::cpp14::make_unique<Wt::WAnchor>(link,
                                                            "Dosyayı İndir");

                {
                    auto text = vLayout->addWidget(std::move(anchor),
                                                   0,
                                                   AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                    text->setMargin(WLength::Auto,AllSides);
                }



            }

            {
                auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_12+
                                         Bootstrap::Grid::Medium::col_md_12+
                                         Bootstrap::Grid::Small::col_sm_12+
                                         Bootstrap::Grid::ExtraSmall::col_xs_12);
                container->setContentAlignment(AlignmentFlag::Center);
                container->setHeight(75);
                container->setAttributeValue(Style::style,Style::background::color::rgba(0,127,65));
                container->setAttributeValue(Style::dataoid,doc["_id"].get_oid().value.to_string().c_str());

                auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                int uyeCount = 0;

                {
                    auto filter = document {};

                    try {
                        filter.append(kvp("_id",bsoncxx::oid(container->attributeValue(Style::dataoid).toUTF8().c_str())));
                    } catch (bsoncxx::exception &e) {

                    }

                    std::vector<std::string> uyetclist;
                    std::vector<int> uyeAcceptedlist;

                    try {

                        auto val = this->getDb()->collection("Projeler").find_one(filter.view());

                        if( val )
                        {

                            try {
                                auto array = val.value().view()["uyeler"].get_array().value;

                                for( auto item : array )
                                {
                                    auto uyeDoc = item.get_document().view()["telno"].get_utf8().value.to_string();
                                    uyetclist.push_back(uyeDoc);
                                    uyeAcceptedlist.push_back(item.get_document().view()["onay"].get_int32().value);
                                    uyeCount++;
                                }

                            } catch (bsoncxx::exception &e) {
                                std::cout << "Line: " << __LINE__ << " ->" <<e.what() << std::endl;
                            }


                        }


                    } catch (mongocxx::exception &e) {

                    }

                    // Hiç Üye Yok ise Kişi Ekle Butonu
                    if (uyetclist.size() == 0) {
                        auto text = vLayout->addWidget(
                                    cpp14::make_unique<WText>(std::string("Kişi Ekle+")),
                                    0, AlignmentFlag::Center | AlignmentFlag::Middle);
                        text->setAttributeValue(
                                    Style::style,
                                    Style::font::size::s10px +
                                    Style::color::color(
                                        Style::color::White::AliceBlue) +
                                    Style::font::weight::lighter);
                        text->setMargin(WLength::Auto, AllSides);

                        text->decorationStyle().setCursor(Cursor::PointingHand);

                        text->clicked().connect([=](){



                            auto mDialog = this->addChild(cpp14::make_unique<WDialog>("Projeye Üye Ekle"));


                            Wt::WLabel *warnlabel =
                                    mDialog->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLabel>("<span style=\"background-color:#000000;color:#ffffff;\">"
                                                                                                      "!Dikkat: Davet Ettiğiniz Kişinin Daha Önceden Üye Olması Gerekmektedir.</span>"));

                            auto uyeTelno = mDialog->contents()->addWidget(cpp14::make_unique<WLineEdit>());
                            uyeTelno->setPlaceholderText("Üye Olacak Kişinin Telefon Numarasını Giriniz");

                            Wt::WLabel *uyari =
                                    mDialog->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLabel>(""));


                            Wt::WPushButton *ok =
                                    mDialog->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Davetiye Gönder"));
                            ok->setDefault(true);

                            Wt::WPushButton *cancel =
                                    mDialog->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("İptal"));
                            mDialog->rejectWhenEscapePressed();


                            ok->clicked().connect([=] {

                                bool exist = false;
                                if( uyeTelno->text().toUTF8().size() != 11 )
                                {
                                    uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">!Hatalı Telefon Numarası</span>");
                                }else if (uyeTelno->text().toUTF8() == this->getCeptel() ) {
                                    uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">!Kendi Projenize Üye Olamazsınız</span>");
                                }else{


                                    auto filter = document{};

                                    try {
                                        filter.append(kvp("ceptelkey",uyeTelno->text().toUTF8()));
                                    } catch (bsoncxx::exception &e) {
                                        std::cout << "UYE TCNO Error: " << e.what() << std::endl;
                                    }

                                    try {
                                        auto count = this->getDb()->collection("Users").count(filter.view());

                                        if( count )
                                        {
                                            exist = true;
                                        }else{
                                            uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">Böyle Bir Kişi Yok</span>");

                                        }


                                    } catch (mongocxx::exception &e) {

                                    }


                                    // Uye Veritabanında var. Projede Üyeliği Var mı?
                                    if( exist )
                                    {

                                        filter.clear();

                                        try {
                                            filter.append(kvp("_id",bsoncxx::oid(container->attributeValue(Style::dataoid).toUTF8().c_str())));
                                        } catch (bsoncxx::exception &e) {

                                        }

                                        try {

                                            auto val = this->getDb()->collection("Projeler").find_one(filter.view());

                                            if( val )
                                            {

                                                int uyeCount = 0;

                                                try {
                                                    auto element = val.value().view()["uyeler"].get_array().value;

                                                    for( auto item : element )
                                                    {
                                                        uyeCount++;
                                                    }

                                                    if( uyeCount > 1 )
                                                    {
                                                        exist = false;
                                                    }


                                                } catch (bsoncxx::exception &e) {
                                                    std::cout << "Line " << __LINE__ << "->val.value().view() in uyeler type " << "array() :"<< e.what() << std::endl;
                                                }

                                            }


                                        } catch (mongocxx::exception &e) {

                                        }
                                    }


                                    if( uyeCount )
                                    {
                                        uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">Bu Kişi Zaten Davet Edilmiş</span>");
                                    }

                                    if( exist )
                                    {
                                        filter.clear();



                                        try {
                                            filter.append(kvp("_id",bsoncxx::oid(container->attributeValue(Style::dataoid).toUTF8().c_str()))) ;
                                        } catch (bsoncxx::exception &e) {
                                            std::cout << "Line " << __LINE__ << ":-> filter Key" << "_id" <<" "<< e.what() << std::endl;
                                        }






                                        auto uyeDoc = document{};

                                        try {
                                            uyeDoc.append(kvp("telno",uyeTelno->text().toUTF8())) ;
                                        } catch (bsoncxx::exception &e) {
                                            std::cout << "Line " << __LINE__ << ":-> uye Key" << "telno" <<" "<< e.what() << std::endl;
                                        }



                                        try {
                                            uyeDoc.append(kvp("onay",bsoncxx::types::b_int32{0})) ;
                                        } catch (bsoncxx::exception &e) {
                                            std::cout << "Line " << __LINE__ << "-> uyeDoc." << "onay :"<< e.what() << std::endl;
                                        }




                                        auto pushDoc = document{};


                                        try {
                                            pushDoc.append(kvp("$push",make_document(kvp("uyeler",uyeDoc)))) ;
                                        } catch (bsoncxx::exception &e) {
                                            std::cout << "Line " << __LINE__ << "-> pushDoc." << "$push :"<< e.what() << std::endl;
                                        }




                                        try {
                                            auto upt = this->getDb()->collection("Projeler").update_one(filter.view(),pushDoc.view());
                                            if( upt )
                                            {
                                                if( upt.value().modified_count() )
                                                {
                                                    mDialog->accept();
                                                }else{
                                                    uyari->setText("<span style=\"background-color:#FA559E;color:#ffffff;\"><b>Davetiye Gönderilemedi</b></span>");
                                                }
                                            }
                                        } catch (mongocxx::exception &e) {
                                            uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">"+std::string(e.what())+"</span>");
                                        }
                                    }
                                }
                            });

                            cancel->clicked().connect(mDialog, &Wt::WDialog::reject);

                            mDialog->finished().connect([=] {
                                if (mDialog->result() == Wt::DialogCode::Accepted)
                                {

                                    this->initProjectList();

                                }else{
                                    this->removeChild(mDialog);
                                }
                            });


                            mDialog->show();

                        });


                    }
                    // Uye Sayısı 1 tane ise Kişi Ekle Butonu ve Uyeyi Göster
                    else if (uyetclist.size() == 1) {

                        auto imgContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Middle);


                        std::string accepted;

                        if( uyeAcceptedlist.at(0) == 1 )
                        {
                            imgContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkGreen));
                            accepted = " (+)";

                        }else if( uyeAcceptedlist.at(0) == 0 ){
                            imgContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::DarkGray));
                            accepted = " (?)";
                        }else{
                            imgContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::FireBrick));
                            accepted = " (-)";
                        }

                        imgContainer->setHeight(25);
                        auto hLayout = imgContainer->setLayout(cpp14::make_unique<WHBoxLayout>());

                        auto filter = bsoncxx::builder::basic::document{};


                        try {

                            filter.append(kvp("ceptelkey",uyetclist.at(0))) ;

                        } catch (bsoncxx::exception &e) {
                            std::cout << "Line: " << __LINE__ << " ->" <<e.what() << std::endl;
                        }



                        try {

                            auto val = this->getDb()->collection("Users").find_one(filter.view());

                            if( val )
                            {
                                auto text = hLayout->addWidget(cpp14::make_unique<WText>(val.value().view()["adsoyad"].get_utf8().value.to_string() + accepted),
                                        0,AlignmentFlag::Center|AlignmentFlag::Middle);

                                text->setAttributeValue(Style::style,Style::font::size::s12px+Style::font::weight::bold+
                                                        Style::color::color(Style::color::White::AliceBlue));

                                if( uyeAcceptedlist.at(0) == 0 || uyeAcceptedlist.at(0) == -1 )
                                {
                                    hLayout->addSpacing(5);


                                    auto text1 = hLayout->addWidget(cpp14::make_unique<WText>("Davetiyeyi İptal Et"),
                                            0,AlignmentFlag::Center|AlignmentFlag::Middle);

                                    text1->setAttributeValue( Style::style , Style::font::size::s12px + Style::font::weight::bold +
                                                            Style::color::color( Style::color::Grey::Black ) );


                                    text1->decorationStyle().setCursor(Cursor::PointingHand);

                                    text1->clicked().connect([=](){

                                        auto filter = document{};



                                        try {
                                            filter.append(kvp("_id",bsoncxx::oid(container->attributeValue(Style::dataoid).toUTF8().c_str()))) ;
                                        } catch (bsoncxx::exception &e) {
                                            std::cout << "Line " << __LINE__ << "-> filter." << "_id :"<< e.what() << std::endl;
                                        }

                                        try {
                                            filter.append(kvp("uyeler.telno",uyetclist.at(0))) ;
                                        } catch (bsoncxx::exception &e) {
                                            std::cout << "Line " << __LINE__ << "-> pullDoc." << "$pull :"<< e.what() << std::endl;
                                        }


                                        auto pullDoc = document{};

                                        try {
                                            pullDoc.append(kvp("$pull",make_document(kvp("uyeler",make_document(kvp("telno",uyetclist.at(0))))))) ;
                                        } catch (bsoncxx::exception &e) {
                                            std::cout << "Line " << __LINE__ << "-> pullDoc." << "$pull :"<< e.what() << std::endl;
                                        }

                                        try {

                                            auto upt = this->getDb()->collection("Projeler").update_one(filter.view(),pullDoc.view());

                                            if( upt.value().modified_count() )
                                            {
                                                this->initProjectList();
                                            }else{
                                                std::cout << "No Updated Project" << std::endl;
                                            }

                                        } catch (mongocxx::exception &e) {
                                            std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
                                        }
                                    });
                                }


                            }



                        } catch (mongocxx::exception &e) {
                            std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
                        }



                        auto text =
                                vLayout -> addWidget(cpp14::make_unique<WText>(
                                                         std::string("Kişi Ekle+")),
                                                     0,
                                                     AlignmentFlag::Center |
                                                     AlignmentFlag::Middle);
                        text->setAttributeValue(
                                    Style::style,
                                    Style::font::size::s10px +
                                    Style::color::color(
                                        Style::color::White::AliceBlue) +
                                    Style::font::weight::lighter);
                        text->setMargin(WLength::Auto, AllSides);

                        text->decorationStyle().setCursor(Cursor::PointingHand);

                        text->clicked().connect([=](){



                            auto mDialog = this->addChild(cpp14::make_unique<WDialog>("Projeye Üye Ekle"));


                            Wt::WLabel *warnlabel =
                                    mDialog->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLabel>("<span style=\"background-color:#000000;color:#ffffff;\">"
                                                                                                      "!Dikkat: Davet Ettiğiniz Kişinin Daha Önceden Üye Olması Gerekmektedir.</span>"));

                            auto uyeTelno = mDialog->contents()->addWidget(cpp14::make_unique<WLineEdit>());
                            uyeTelno->setPlaceholderText("Üye Olacak Kişinin Telefon Numarasını Giriniz");

                            Wt::WLabel *uyari =
                                    mDialog->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLabel>(""));


                            Wt::WPushButton *ok =
                                    mDialog->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Davetiye Gönder"));
                            ok->setDefault(true);

                            Wt::WPushButton *cancel =
                                    mDialog->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("İptal"));
                            mDialog->rejectWhenEscapePressed();


                            ok->clicked().connect([=] {

                                bool exist = false;

                                if( uyeTelno->text().toUTF8().size() != 11 )
                                {
                                    uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">!Hatalı Telefon Numarası</span>");
                                }else if (uyeTelno->text().toUTF8() == this->getCeptel() ) {
                                    uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">!Kendi Projenize Üye Olamazsınız</span>");
                                }else{


                                    auto filter = document{};

                                    try {
                                        filter.append(kvp("ceptelkey",uyeTelno->text().toUTF8()));
                                    } catch (bsoncxx::exception &e) {
                                        std::cout << "UYE TCNO Error: " << e.what() << std::endl;
                                    }

                                    try {
                                        auto count = this->getDb()->collection("Users").count(filter.view());

                                        if( count )
                                        {
                                            exist = true;
                                        }else{
                                            uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">Böyle Bir Kişi Yok</span>");
                                        }


                                    } catch (mongocxx::exception &e) {

                                    }


                                    filter.clear();

                                    try {
                                        filter.append(kvp("_id",bsoncxx::oid(container->attributeValue(Style::dataoid).toUTF8().c_str())));
                                    } catch (bsoncxx::exception &e) {

                                    }

                                    bool kisiZatenUye = false;
                                    try {

                                        auto val = this->getDb()->collection("Projeler").find_one(filter.view());

                                        if( val )
                                        {
                                            auto array = val.value().view()["uyeler"].get_array().value;

                                            int uyeCount = 0;

                                            exist = true;
                                            for( auto item : array )
                                            {
                                                try {
                                                    auto value = item.get_document().view()["telno"].get_utf8().value.to_string();
                                                    std::cout << "UYETELNO: " << value << " : " << uyeTelno->text().toUTF8() << std::endl;
                                                    if( value == uyeTelno->text().toUTF8() )
                                                    {
                                                        kisiZatenUye = true;
                                                        uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">Bu Kişi Zaten Üye</span>");
                                                    }
                                                } catch (bsoncxx::exception &e) {
                                                    std::cout << "Line " << __LINE__ << "->in item.get_document().view() telno type is not " << "get_utf8() :"<< e.what() << std::endl;
                                                }
                                                uyeCount++;

                                            }

                                            if( uyeCount > 1 )
                                            {
                                                exist = false;
                                            }
                                        }


                                    } catch (mongocxx::exception &e) {

                                    }



                                    if( exist && !kisiZatenUye )
                                    {
                                        filter.clear();

                                        try {
                                            filter.append(kvp("_id",bsoncxx::oid(container->attributeValue(Style::dataoid).toUTF8().c_str())));
                                        } catch (bsoncxx::exception &e) {

                                        }

                                        auto uyeDoc = document{};

                                        try {
                                            uyeDoc.append(kvp("telno",uyeTelno->text().toUTF8()));
                                        } catch (bsoncxx::exception &e) {

                                        }

                                        try {
                                            uyeDoc.append(kvp("onay",bsoncxx::types::b_int32{0}));
                                        } catch (bsoncxx::exception &e) {

                                        }


                                        auto pushDoc = document{};

                                        try {
                                            pushDoc.append(kvp("$push",make_document(kvp("uyeler",uyeDoc))));
                                        } catch (bsoncxx::exception &e) {

                                        }

                                        try {
                                            auto upt = this->getDb()->collection("Projeler").update_one(filter.view(),pushDoc.view());
                                            if( upt )
                                            {
                                                if( upt.value().modified_count() )
                                                {
                                                    mDialog->accept();
                                                }else{
                                                    uyari->setText("<span style=\"background-color:#FA559E;color:#ffffff;\"><b>Davetiye Gönderilemedi</b></span>");
                                                }
                                            }
                                        } catch (mongocxx::exception &e) {
                                            uyari->setText("<span style=\"background-color:#B4009E;color:#ffffff;\">"+std::string(e.what())+"</span>");
                                        }
                                    }
                                }



                            });

                            cancel->clicked().connect(mDialog, &Wt::WDialog::reject);

                            mDialog->finished().connect([=] {
                                if (mDialog->result() == Wt::DialogCode::Accepted)
                                {

                                    this->initProjectList();

                                }else{
                                    this->removeChild(mDialog);
                                }
                            });


                            mDialog->show();

                        });




                    }
                    // Eğer Üye Sayısı 2 Adet ise
                    else {

                        int i = 0;
                        for( auto tcno : uyetclist )
                        {
                            auto imgContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Middle);


                            std::string accepted;

                            if( uyeAcceptedlist.at(i) == 1 )
                            {
                                imgContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkGreen));
                                accepted = " (+)";

                            }else if( uyeAcceptedlist.at(i) == 0 ){
                                imgContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::DarkGray));
                                accepted = " (?)";
                            }else{
                                imgContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::FireBrick));
                                accepted = " (-)";
                            }

                            imgContainer->setHeight(25);
                            auto hLayout = imgContainer->setLayout(cpp14::make_unique<WHBoxLayout>());

                            auto filter = bsoncxx::builder::basic::document{};


                            try {

                                filter.append(kvp("ceptelkey",uyetclist.at(i))) ;

                            } catch (bsoncxx::exception &e) {
                                std::cout << "Line: " << __LINE__ << " ->" <<e.what() << std::endl;
                            }



                            try {

                                auto val = this->getDb()->collection("Users").find_one(filter.view());

                                if( val )
                                {
                                    auto text = hLayout->addWidget(cpp14::make_unique<WText>(val.value().view()["adsoyad"].get_utf8().value.to_string() + accepted),
                                            0,AlignmentFlag::Center|AlignmentFlag::Middle);

                                    text->setAttributeValue(Style::style,Style::font::size::s12px+Style::font::weight::bold+
                                                            Style::color::color(Style::color::White::AliceBlue));

                                    if( uyeAcceptedlist.at(i) == 0 || uyeAcceptedlist.at(i) == -1 )
                                    {
                                        hLayout->addSpacing(5);


                                        auto text1 = hLayout->addWidget(cpp14::make_unique<WText>("Davetiyeyi İptal Et"),
                                                0,AlignmentFlag::Center|AlignmentFlag::Middle);

                                        text1->setAttributeValue( Style::style , Style::font::size::s12px + Style::font::weight::bold +
                                                                Style::color::color( Style::color::Grey::Black ) );

                                        text1->decorationStyle().setCursor(Cursor::PointingHand);

                                        text1->clicked().connect([=](){

                                            auto filter = document{};



                                            try {
                                                filter.append(kvp("_id",bsoncxx::oid(container->attributeValue(Style::dataoid).toUTF8().c_str()))) ;
                                            } catch (bsoncxx::exception &e) {
                                                std::cout << "Line " << __LINE__ << "-> filter." << "_id :"<< e.what() << std::endl;
                                            }

                                            try {
                                                filter.append(kvp("uyeler.telno",uyetclist.at(i))) ;
                                            } catch (bsoncxx::exception &e) {
                                                std::cout << "Line " << __LINE__ << "-> pullDoc." << "$pull :"<< e.what() << std::endl;
                                            }

                                            auto tcDoc = document{};

                                            try {
                                                tcDoc.append(kvp("telno",uyetclist.at(i))) ;
                                            } catch (bsoncxx::exception &e) {
                                                std::cout << "Line " << __LINE__ << "-> tcDoc." << "tcno :"<< e.what() << std::endl;
                                            }

                                            try {
                                                tcDoc.append(kvp("onay",bsoncxx::types::b_int32{uyeAcceptedlist.at(i)})) ;
                                            } catch (bsoncxx::exception &e) {
                                                std::cout << "Line " << __LINE__ << "-> tcDoc." << "tcno :"<< e.what() << std::endl;
                                            }

                                            auto pullDoc = document{};

                                            try {
                                                pullDoc.append(kvp("$pull",make_document(kvp("uyeler",make_document(kvp("telno",uyetclist.at(i))))))) ;
                                            } catch (bsoncxx::exception &e) {
                                                std::cout << "Line " << __LINE__ << "-> pullDoc." << "$pull :"<< e.what() << std::endl;
                                            }

                                            try {

                                                auto upt = this->getDb()->collection("Projeler").update_one(filter.view(),pullDoc.view());

                                                if( upt.value().modified_count() )
                                                {
                                                    this->initProjectList();
                                                }else{
                                                    std::cout << "No Updated Project" << std::endl;
                                                }

                                            } catch (mongocxx::exception &e) {
                                                std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
                                            }
                                        });
                                    }
                                }


                            } catch (mongocxx::exception &e) {
                                std::cout << "Line: " << __LINE__ << "  ->" <<e.what() << std::endl;
                            }

                            i++;
                        }



                        //                        {
                        //                            auto imgContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Middle);
                        //                            imgContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::Crimson));
                        //                            imgContainer->setHeight(25);
                        //                        }

                        //                        {
                        //                            auto imgContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Middle);
                        //                            imgContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkSalmon));
                        //                            imgContainer->setHeight(25);
                        //                        }


                    }

                }



            }
        }




    } catch (mongocxx::exception &e) {
        this->ShowMessage(std::string("Hata: ") + e.what());
        return;
    }
}

void Project::initController()
{
    mController->clear();

    auto contentContainer = mController->addWidget(cpp14::make_unique<WContainerWidget>());

    auto fContainer = contentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    container->addStyleClass(Bootstrap::Grid::col_full_12);

    auto hLayout = container->setLayout(cpp14::make_unique<WHBoxLayout>());

    auto ekle = hLayout->addWidget(cpp14::make_unique<WPushButton>("Yeni Proje Ekle"),0,AlignmentFlag::Right);
    ekle->addStyleClass(Bootstrap::Button::Primary);

    ekle->clicked().connect(this,&Project::initNewProject);

}

void Project::initNewProject()
{

    mNewContainer->clear();

    mNewContainer->setContentAlignment(AlignmentFlag::Center);
    auto fContainer = mNewContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    fContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        mProjectName = container->addWidget(cpp14::make_unique<WLineEdit>());
        mProjectName->setPlaceholderText("Proje Adını Giriniz");
    }

    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        mKategori = container->addWidget(cpp14::make_unique<WComboBox>());
        mKategori->addItem("Kategori Seçiniz");
        mKategori->addItem("Toplumsal");
        mKategori->addItem("Çevresel");
        mKategori->addItem("Kültürel");
        mKategori->addItem("Eğitim");

    }


    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);


        Wt::WFileUpload *fu = container->addWidget(Wt::cpp14::make_unique<Wt::WFileUpload>());


        //        fu->setFileTextSize(500); // Set the maximum file size to 50 kB.
        fu->setProgressBar(Wt::cpp14::make_unique<Wt::WProgressBar>());
        //        fu->setMargin(10, Wt::Side::Right);



        Wt::WText *out = rContainer->addWidget(Wt::cpp14::make_unique<Wt::WText>());



        fu->changed().connect([=] {
            fu->upload();
            out->setText("File upload is changed");
        });



        fu->uploaded().connect([=] {
            if( fu->uploadedFiles().size() )
            {
                out->setText("Yükleme Tamamlandı");
                for( auto item : fu->uploadedFiles() )
                {
                    clientFileName = item.clientFileName();
                    uploadedfilefullpath = item.spoolFileName();
                }
            }
        });

        // React to a file upload problem.
        fu->fileTooLarge().connect([=] {
            out->setText("Dosya Fazla Büyük Dosya Boyutunu Düşürün");
        });
    }





    {
        auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        auto kaydet = container->addWidget(cpp14::make_unique<WPushButton>("Kaydet"));
        kaydet->addStyleClass(Bootstrap::Button::info);
        kaydet->clicked().connect([=](){

            if( !this->mProjectName->text().toUTF8().size() )
            {
                this->ShowMessage("Proje Adını Boş Geçemezsiniz");
                return;
            }



            if( this->mKategori->currentIndex() == 0 )
            {
                this->ShowMessage("Kategori Seçmediniz");
                return;
            }



            QFileInfo info( this->clientFileName.c_str() );

            auto fileid = this->uploadfile(this->uploadedfilefullpath.c_str());

            auto doc = document{};

            try {
                doc.append(kvp("projeadi",mProjectName->text().toUTF8()));
            } catch (bsoncxx::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            try {
                doc.append(kvp("projeKategori",mKategori->currentText().toUTF8()));
            } catch (bsoncxx::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            try {
                doc.append(kvp("projeadi",mProjectName->text().toUTF8()));
            } catch (bsoncxx::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            try {
                doc.append(kvp("dosyaadi",clientFileName));
            } catch (bsoncxx::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            try {
                doc.append(kvp("dosya",fileid));
            } catch (bsoncxx::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            try {
                doc.append(kvp("tcno",this->getTcno()));
            } catch (bsoncxx::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

            try {
                auto ins = this->getDb()->collection("Projeler").insert_one(doc.view());

                if( ins )
                {
                    if( !ins.value().result().inserted_count() )
                    {
                        this->ShowMessage("Proje Dosyanız Yüklenemedi. Lütfen Tekrar Deneyiniz.");
                    }else{
                        this->ShowMessage("Proje Yüklemeniz Başarıyla Yapıldı.");
                        this->initProjectList();
                    }
                }

            } catch (mongocxx::exception &e) {
                std::cout << "proje insert error: " << e.what() << std::endl;
            }

            mNewContainer->clear();

        });
    }


}

int32_t Project::deleteProject(string projectOid)
{


    auto filter = document{};

    try {
        filter.append(kvp("_id",bsoncxx::oid(projectOid)));
    } catch (bsoncxx::exception &e) {
        std::cout << "delete Filter Error: " << e.what() << std::endl;
    }


    try {
        auto del = this->getDb()->collection("Projeler").delete_one(filter.view());

        if( del )
        {
            return del.value().deleted_count();
        }else{
            return 0;
        }

    } catch (mongocxx::exception &e) {
        std::cout << "Delete Mongocxx Error: "<<e.what() << std::endl;
        return 0;
    }

}

std::string Project::downloadProjectFile(string fileoid)
{

    return this->download(bsoncxx::oid(fileoid));

}
