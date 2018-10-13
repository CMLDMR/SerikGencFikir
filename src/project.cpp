#include "project.h"
#include <Wt/WHBoxLayout.h>
#include <Wt/WComboBox.h>
#include <Wt/WFileUpload.h>
#include <Wt/WProgressBar.h>
#include <Wt/WVBoxLayout.h>

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
    initProjectList();

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
            fContainer->setMargin(2,Side::Top);


            auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            rContainer->addStyleClass(Bootstrap::Grid::row);

            {
                auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+
                                         Bootstrap::Grid::Medium::col_md_6+
                                         Bootstrap::Grid::Small::col_sm_12+
                                         Bootstrap::Grid::ExtraSmall::col_xs_6);
                container->setContentAlignment(AlignmentFlag::Center);
//                container->setHeight(100);

                auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                {
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(std::string("Proje Adı")),
                            0,
                            AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                    text->setMargin(WLength::Auto,AllSides);
                }

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
//                container->setHeight(100);

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
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+
                                         Bootstrap::Grid::Medium::col_md_2+
                                         Bootstrap::Grid::Small::col_sm_3+
                                         Bootstrap::Grid::ExtraSmall::col_xs_6);
                container->setContentAlignment(AlignmentFlag::Center);
                container->setHeight(50);
                container->setAttributeValue(Style::style,Style::background::color::rgba(127,0,0));

                auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                {
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(std::string("Sil")),
                            0,
                            AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                    text->setMargin(WLength::Auto,AllSides);
                }
            }

            {
                auto container = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+
                                         Bootstrap::Grid::Medium::col_md_2+
                                         Bootstrap::Grid::Small::col_sm_3+
                                         Bootstrap::Grid::ExtraSmall::col_xs_6);
                container->setContentAlignment(AlignmentFlag::Center);
                container->setHeight(50);
                container->setAttributeValue(Style::style,Style::background::color::rgba(0,127,0));

                auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                {
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>(std::string("Dosyayı İndir")),
                            0,
                            AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                    text->setMargin(WLength::Auto,AllSides);
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
