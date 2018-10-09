#include "body.h"
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>


Body::Body::Body()
{
    setContentAlignment(AlignmentFlag::Center);
    addStyleClass("body");
    mMainContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    mMainContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    mMainContainer->setMaximumSize(1024,WLength::Auto);



    this->initMainPage();
}

void Body::Body::initMainPage()
{

    mMainContainer->clear();

    auto row = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    row->addStyleClass(Bootstrap::Grid::row);


    {
        auto gencfikirLogo = row->addWidget(cpp14::make_unique<WContainerWidget>());

        gencfikirLogo->addStyleClass(Bootstrap::Grid::col_full_12);
        gencfikirLogo->setContentAlignment(AlignmentFlag::Center);
        gencfikirLogo->setMargin(50,Side::Top|Side::Bottom);
        auto logo = gencfikirLogo->addWidget(cpp14::make_unique<WContainerWidget>());
        logo->setWidth(WLength("100%"));
        logo->setMaximumSize(500,WLength::Auto);
        logo->setHeight(182);
        logo->setAttributeValue(Style::style,Style::background::url("icon/intrologo.png")+
                                Style::background::repeat::norepeat);
    }



    {
        auto gencfikirLogo = row->addWidget(cpp14::make_unique<WContainerWidget>());

        gencfikirLogo->addStyleClass(Bootstrap::Grid::col_full_12);
        gencfikirLogo->setContentAlignment(AlignmentFlag::Center);
        gencfikirLogo->setMargin(0,Side::Top);
        gencfikirLogo->setMargin(0,Side::Bottom);
        auto logo = gencfikirLogo->addWidget(cpp14::make_unique<WContainerWidget>());
        logo->setWidth(WLength("100%"));
        logo->setMaximumSize(450,WLength::Auto);
        logo->setHeight(182);
        logo->setAttributeValue(Style::style,Style::background::url("icon/project.png")+
                                Style::background::repeat::norepeat);
    }

    {
        auto gencfikirLogo = row->addWidget(cpp14::make_unique<WContainerWidget>());
        gencfikirLogo->addStyleClass("sonbasvuruShadow");
        gencfikirLogo->addStyleClass(Bootstrap::Grid::col_full_12);
        gencfikirLogo->setContentAlignment(AlignmentFlag::Center);
        gencfikirLogo->setAttributeValue(Style::style,Style::background::color::rgba(255,255,255,0.75));
        gencfikirLogo->setPadding(75,Side::Bottom|Side::Top);

        auto logo = gencfikirLogo->addWidget(cpp14::make_unique<WText>("Son Başvuru Tarihi: 16 Kasım 2018"));
        logo->setAttributeValue(Style::style,Style::font::size::s24px+Style::font::weight::lighter+Style::color::color("black"));
        logo->setMargin(15,Side::Bottom|Side::Top);

        auto logolist = gencfikirLogo->addWidget(cpp14::make_unique<WContainerWidget>());
        logolist->addStyleClass(Bootstrap::Grid::container_fluid);
        logolist->setMargin(15,Side::Bottom|Side::Top);
        auto layout = logolist->setLayout(cpp14::make_unique<WHBoxLayout>());
        layout->addStretch(1);
        const int _width = 50;
        const int _height = 50;
        {
            auto logo1 = layout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);
            logo1->setAttributeValue(Style::style,Style::background::url("icon/logo.png")+
                                     Style::background::position::center_center+Style::background::repeat::norepeat+Style::background::size::contain);
            logo1->setWidth(_width);
            logo1->setHeight(_height);
        }
        {
            auto logo1 = layout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);
            logo1->setAttributeValue(Style::style,Style::background::url("icon/logomilli.png")+
                                     Style::background::position::center_center+Style::background::repeat::norepeat+Style::background::size::contain);
            logo1->setWidth(_width);
            logo1->setHeight(_height);
        }
        {
            auto logo1 = layout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);
            logo1->setAttributeValue(Style::style,Style::background::url("icon/logoserik.png")+
                                     Style::background::position::center_center+Style::background::repeat::norepeat+Style::background::size::contain);
            logo1->setWidth(_width);
            logo1->setHeight(_height);
        }
        {
            auto logo1 = layout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);
            logo1->setAttributeValue(Style::style,Style::background::url("icon/akdeniz.png")+
                                     Style::background::position::center_center+Style::background::repeat::norepeat+Style::background::size::contain);
            logo1->setWidth(_width);
            logo1->setHeight(_height);
        }
        layout->addStretch(1);

        {
            auto explain = gencfikirLogo->addWidget(cpp14::make_unique<WText>("Bu Proje Yarışması Serik Belediyesi, Akdeniz Üniversitesi ve Akev Üniversitesi ile Birlikte Ortaklaşa Yürütülmektedir."));
            explain->setAttributeValue(Style::style,Style::font::size::s16px+Style::font::weight::lighter+Style::color::color("black"));
        }

    }
}

void Body::Body::gencFikirInit()
{

    mMainContainer->clear();

    auto  row = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    row->addStyleClass(Bootstrap::Grid::row);

    {
        auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(50,Side::Bottom|Side::Top);
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        auto text = container->addWidget(cpp14::make_unique<WText>("\"Serik Genç Fikir 2018 Üniversite\" Yarışması Nedir?"));
        text->setAttributeValue(Style::style,Style::font::size::s28px+Style::color::color(Style::color::White::AliceBlue));
    }

    {
        auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(25,Side::Bottom|Side::Top);
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        auto text = container->addWidget(cpp14::make_unique<WText>("Üniversite Öğrencilerinin Katılabileceği <b><i>sosyal sorumluluk proje fikirleri</i></b> yarışmasıdır.",TextFormat::UnsafeXHTML));
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    }

    {
        auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(25,Side::Bottom|Side::Top);
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        auto text = container->addWidget(cpp14::make_unique<WText>("Amaç"));
        text->setAttributeValue(Style::style,Style::font::size::s24px+Style::color::color(Style::color::White::AliceBlue));
    }

    {
        auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(25,Side::Bottom|Side::Top);
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        auto text = container->addWidget(cpp14::make_unique<WText>("Yarışmanın amacı; lise öğrencilerinin sosyal sorumluluk konusunda bilinçlenmelerini, düşünmelerini ve harekete geçmelerini sağlamak, sosyal sorumluluk konusundaki vizyonlarını genişletip öğrencileri motive ederek başarıyı ödüllendirmektir",TextFormat::UnsafeXHTML));
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    }

    {
        auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(25,Side::Top);
        container->setMargin(200,Side::Bottom);
        container->addStyleClass(Bootstrap::Grid::col_full_12);

        auto layout = container->setLayout(cpp14::make_unique<WHBoxLayout>());

        layout->addStretch(1);
        {
            auto img = layout->addWidget(cpp14::make_unique<WContainerWidget>());
            img->setWidth(75);
            img->setHeight(75);
            img->setAttributeValue(Style::style,Style::background::url("icon/icons/1.jpeg")+Style::background::repeat::norepeat+Style::background::size::contain);
        }
        {
            auto img = layout->addWidget(cpp14::make_unique<WContainerWidget>());
            img->setWidth(75);
            img->setHeight(75);
            img->setAttributeValue(Style::style,Style::background::url("icon/icons/2.jpeg")+Style::background::repeat::norepeat+Style::background::size::contain);
        }
        {
            auto img = layout->addWidget(cpp14::make_unique<WContainerWidget>());
            img->setWidth(75);
            img->setHeight(75);
            img->setAttributeValue(Style::style,Style::background::url("icon/icons/3.jpeg")+Style::background::repeat::norepeat+Style::background::size::contain);
        }
        {
            auto img = layout->addWidget(cpp14::make_unique<WContainerWidget>());
            img->setWidth(75);
            img->setHeight(75);
            img->setAttributeValue(Style::style,Style::background::url("icon/icons/4.jpeg")+Style::background::repeat::norepeat+Style::background::size::contain);
        }
        {
            auto img = layout->addWidget(cpp14::make_unique<WContainerWidget>());
            img->setWidth(75);
            img->setHeight(75);
            img->setAttributeValue(Style::style,Style::background::url("icon/icons/5.jpeg")+Style::background::repeat::norepeat+Style::background::size::contain);
        }
        layout->addStretch(1);



    }


}
