#include "footer.h"
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>
#include <Wt/WHBoxLayout.h>


Footer::Footer::Footer()
{

    this->initFooter();

}

Footer::Footer::~Footer()
{

}

void Footer::Footer::initFooter()
{

    auto mContainer = addWidget(cpp14::make_unique<WContainerWidget>());
    mContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    mContainer->setAttributeValue(Style::style,Style::background::color::color("black"));

    mContainer->setContentAlignment(AlignmentFlag::Center);

    auto row = mContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    row->setMaximumSize(1024,WLength::Auto);
    row->setMargin(25,Side::Bottom|Side::Top);

    {
        auto text = row->addWidget(cpp14::make_unique<WText>("ŞŞBu Web Sitesi Serik Belediyesi Bilgi İşlem Müdürlüğü Tarafından Açık Kaynak Kodlu Olarak Geliştirilmektedir."));
        text->addStyleClass(Bootstrap::Grid::col_full_12);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s12px+Style::font::weight::lighter);
    }


    {


        auto container = row->addWidget(cpp14::make_unique<WContainerWidget>());

        auto layout = container->setLayout(cpp14::make_unique<WHBoxLayout>());

        layout->addStretch(1);

        {
            auto t = layout->addWidget(cpp14::make_unique<WText>("© Copyright 2018 "));
            t->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s12px+Style::font::weight::lighter);

        }
        {
            Wt::WLink link = Wt::WLink("https://www.webtoolkit.eu/");
            link.setTarget(Wt::LinkTarget::NewWindow);

            std::unique_ptr<Wt::WAnchor> anchor =
                    Wt::cpp14::make_unique<Wt::WAnchor>(link,
                                    "Wt");

            auto t = layout->addWidget(std::move(anchor));
        }
        {
            auto t = layout->addWidget(cpp14::make_unique<WText>(" & "));
            t->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s12px+Style::font::weight::lighter);

        }
        {
            Wt::WLink link = Wt::WLink("https://github.com/CMLDMR/SerikGencFikir");
            link.setTarget(Wt::LinkTarget::NewWindow);

            std::unique_ptr<Wt::WAnchor> anchor =
                    Wt::cpp14::make_unique<Wt::WAnchor>(link,
                                    "gitHub");

            auto t = layout->addWidget(std::move(anchor));
        }
        layout->addStretch(1);

    }



}
