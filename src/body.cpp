#include "body.h"
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>


Body::Body::Body()
{
    setContentAlignment(AlignmentFlag::Center);
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

        gencfikirLogo->addStyleClass(Bootstrap::Grid::col_full_12);
        gencfikirLogo->setContentAlignment(AlignmentFlag::Center);
        gencfikirLogo->setAttributeValue(Style::style,Style::background::color::color(Style::color::Purple::DarkSlateBlue));
        auto logo = gencfikirLogo->addWidget(cpp14::make_unique<WText>("Son Başvuru Tarihi: 23 Kasım 2018"));
        logo->setAttributeValue(Style::style,Style::font::size::s24px+Style::font::weight::lighter+Style::color::color(Style::color::White::FloralWhite));


        auto logolist = gencfikirLogo->addWidget(cpp14::make_unique<WContainerWidget>());
        logolist->addStyleClass(Bootstrap::Grid::container_fluid);
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
        layout->addStretch(1);

        {
            auto explain = gencfikirLogo->addWidget(cpp14::make_unique<WText>("Bu Proje Yarışması Serik Belediyesi ve Serik ... ile Birlikte Ortaklaşa Yürütülmektedir."));
            explain->setAttributeValue(Style::style,Style::font::size::s16px+Style::font::weight::lighter+Style::color::color(Style::color::White::FloralWhite));
        }

    }
}

void Body::Body::gencFikirInit()
{

    mMainContainer->clear();

    auto  row = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());


    auto title = row->addWidget(cpp14::make_unique<WText>("GEnç Fikir Nedir?"));



}
