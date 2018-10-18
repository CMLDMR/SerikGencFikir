#include "davetiyewidget.h"

#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>

DavetiyeWidget::DavetiyeWidget(mongocxx::database *_db, bsoncxx::document::view userDocument)
    :BaseWidget (_db),User (userDocument)
{

//    mUser = new  User(userDocument);

    setMargin(15,Side::Bottom|Side::Top);

    mContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    mContainer->addStyleClass(Bootstrap::Grid::container_fluid);

    {
        auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        row->addStyleClass(Bootstrap::Grid::row);

        auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setMargin(15,Side::Top|Side::Bottom);

        container->setContentAlignment(AlignmentFlag::Center|AlignmentFlag::Middle);

        auto text = container->addWidget(cpp14::make_unique<WText>("Gelen Proje Davetleri"));
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Azure)+Style::font::size::s18px+Style::font::weight::bold);

    }

    mRow = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    mRow->addStyleClass(Bootstrap::Grid::row);




    this->initDavetiler();



}

void DavetiyeWidget::initDavetiler()
{

    mRow->clear();

    auto filter = document{};

    try {
        filter.append(kvp("uyeler",make_document(kvp("$elemMatch",make_document(kvp("telno",this->getCeptel()))))));
    } catch (bsoncxx::exception &e) {

    }



    try {
        auto cursor = this->getDb()->collection("Projeler").find(filter.view());

        for( auto doc : cursor )
        {

            auto container = mRow->addWidget(cpp14::make_unique<WContainerWidget>());
            container->addStyleClass( Bootstrap::Grid::col_full_12 );
            container->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0)+Style::Border::borderRardius("15","15","5","5")+Style::Border::border("1px solid white"));
            container->setMargin(10,Side::Bottom);

            auto fContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            fContainer->addStyleClass( Bootstrap::Grid::container_fluid );
            fContainer->setMargin(5,Side::Top|Side::Bottom);


            auto rContainer = fContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            rContainer->addStyleClass( Bootstrap::Grid::row );

            {
                auto itemContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                itemContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);
                auto vLayout = itemContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
                auto text = vLayout->addWidget(cpp14::make_unique<WText>(doc["projeadi"].get_utf8().value.to_string()),0,AlignmentFlag::Middle|AlignmentFlag::Center);
                text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Azure)+Style::font::size::s16px+Style::font::weight::bold);
            }

            {
                auto itemContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                itemContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_3+Bootstrap::Grid::ExtraSmall::col_xs_6);
                auto vLayout = itemContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
                auto text = vLayout->addWidget(cpp14::make_unique<WText>(doc["projeKategori"].get_utf8().value.to_string()),0,AlignmentFlag::Middle|AlignmentFlag::Center);
                text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Azure)+Style::font::size::s16px+Style::font::weight::bold);
            }

            {
                auto itemContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                itemContainer->setHeight(50);
                itemContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_3+Bootstrap::Grid::ExtraSmall::col_xs_6);
                itemContainer->setAttributeValue(Style::style,Style::background::color::rgba(25,75,125));
                auto vLayout = itemContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
//                auto text = vLayout->addWidget(cpp14::make_unique<WText>("Projeye Bak"),0,AlignmentFlag::Middle|AlignmentFlag::Center);
//                text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Azure)+Style::font::size::s16px+Style::font::weight::bold);

                auto downloadlink = this->download(doc["dosya"].get_oid().value);


                QFileInfo
                    info(doc["dosyaadi"].get_utf8().value.to_string().c_str());

                QString newFileName =
                    QString("docroot/tempfile/") +
                                      doc["dosya"].get_oid().value.to_string().c_str() +
                    "." + info.suffix().toStdString().c_str();

                QString downloadFileName = QString("tempfile/")+doc["dosya"].get_oid().value.to_string().c_str() + "." +info.suffix().toStdString().c_str();

                std::cout << "File Renamed: " << QFile::rename(QString("docroot/")+downloadlink.c_str(),newFileName) << std::endl;


                Wt::WLink link = Wt::WLink(downloadFileName.toStdString());
                link.setTarget(Wt::LinkTarget::NewWindow);

                std::unique_ptr<Wt::WAnchor> anchor =
                    Wt::cpp14::make_unique<Wt::WAnchor>(link, "Projeye Bak");

                {
                    auto text = vLayout->addWidget(std::move(anchor),
                                                   0,
                                                   AlignmentFlag::Center|AlignmentFlag::Middle );
                    text->setAttributeValue(Style::style,Style::font::size::s14px+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                    text->setMargin(WLength::Auto,AllSides);
                }


            }


            {
                try {
                    auto uyelist = doc["uyeler"].get_array().value;

                    bool exist = false;

                    for( auto item : uyelist )
                    {
                        if( item.get_document().view()["telno"].get_utf8().value.to_string() == this->getCeptel() &&
                                item.get_document().view()["onay"].get_int32().value == 0 )
                        {
                            exist = true;
                            break;
                        }
                    }

                    if( exist )
                    {
                        auto ControllerContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());

                        ControllerContainer->addStyleClass(Bootstrap::Grid::col_full_12);

                        auto hLayout = ControllerContainer->setLayout(cpp14::make_unique<WHBoxLayout>());

                        hLayout->addStretch(1);

                        {
                            auto itemContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                            itemContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
                            auto text = hLayout->addWidget(cpp14::make_unique<WPushButton>("Kabul Et"));
                            text->addStyleClass(Bootstrap::Button::Success);
                            itemContainer->setAttributeValue(Style::dataoid,doc["_id"].get_oid().value.to_string());



                            text->clicked().connect([=](){




                                auto filter = document{};

                                try {
                                    filter.append(kvp("_id",bsoncxx::oid(itemContainer->attributeValue(Style::dataoid).toUTF8())));
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Filter Error: " << e.what() << std::endl;
                                }

                                try {
                                    filter.append(kvp("uyeler.telno",this->getCeptel()));
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Filter Error: " << e.what() << std::endl;
                                }

                                auto setDoc = document{};


                                try {
                                    setDoc.append(kvp("$set",make_document(kvp("uyeler.$.onay",1))));
                                } catch (bsoncxx::exception &e) {

                                }

                                try {

                                    auto upt = this->getDb()->collection("Projeler").update_one(filter.view(),setDoc.view());

                                    if( upt )
                                    {
                                        this->initDavetiler();
                                    }else{
                                        std::cout << "No Document Updated"  << std::endl;
                                    }

                                } catch (mongocxx::exception &e) {
                                    std::cout << "Error: " << e.what() << std::endl;
                                }




                            });
                        }

                        {
                            auto itemContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                            itemContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
                            auto text = hLayout->addWidget(cpp14::make_unique<WPushButton>("Red Et"));
                            text->addStyleClass(Bootstrap::Button::Danger);

                            itemContainer->setAttributeValue(Style::dataoid,doc["_id"].get_oid().value.to_string());
                            text->clicked().connect([=](){

                                auto filter = document{};

                                try {
                                    filter.append(kvp("_id",bsoncxx::oid(itemContainer->attributeValue(Style::dataoid).toUTF8())));
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Filter Error: " << e.what() << std::endl;
                                }

                                try {
                                    filter.append(kvp("uyeler.telno",this->getCeptel()));
                                } catch (bsoncxx::exception &e) {
                                    std::cout << "Filter Error: " << e.what() << std::endl;
                                }

                                auto setDoc = document{};


                                try {
                                    setDoc.append(kvp("$set",make_document(kvp("uyeler.$.onay",-1))));
                                } catch (bsoncxx::exception &e) {

                                }

                                try {

                                    auto upt = this->getDb()->collection("Projeler").update_one(filter.view(),setDoc.view());

                                    if( upt )
                                    {
                                        std::cout << "UPDATE: " << upt.value().modified_count() << std::endl;
                                    }else{
                                        std::cout << "No Document Updated"  << std::endl;
                                    }

                                } catch (mongocxx::exception &e) {
                                    std::cout << "Error: " << e.what() << std::endl;
                                }




                            });
                        }
                        hLayout->addStretch(1);
                    }

                } catch (bsoncxx::exception &e) {

                }

            }




        }

    } catch (mongocxx::exception &e) {
        std::cout << "Mongocxx Davetiler Queryt Error: " << e.what() << std::endl;
    }



}
