#include "header.h"

Header::Header::Header()
{
    setZIndex(10);
    setHeight(100);
    setAttributeValue(Style::style,Style::background::color::rgb(51,102,153));
    setPositionScheme(PositionScheme::Relative);
    addStyleClass(Bootstrap::Grid::container_fluid);

    auto row = addWidget(cpp14::make_unique<WContainerWidget>());
    row->addStyleClass(Bootstrap::Grid::row);





    auto navcontainer = row->addWidget(cpp14::make_unique<WContainerWidget>());
    navcontainer->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
    navcontainer->setAttributeValue(Style::style,Style::background::color::rgb(51,102,153));
    navcontainer->setMargin(WLength::Auto,Side::Left|Side::Right);
    navcontainer->setContentAlignment(AlignmentFlag::Center);


    auto mainContainer = navcontainer->addWidget(cpp14::make_unique<WContainerWidget>());
    mainContainer->addStyleClass(Bootstrap::Grid::container_fluid);
    mainContainer->setMaximumSize(1024,WLength::Auto);

    auto sRow = mainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    sRow->addStyleClass(Bootstrap::Grid::row);


    {
        auto logoCOntainer = sRow->addWidget(cpp14::make_unique<WContainerWidget>());
        logoCOntainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_2+Bootstrap::Grid::ExtraSmall::col_xs_3);
        logoCOntainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Purple::BlueViolet));
        logoCOntainer->setHeight(100);
        logoCOntainer->setAttributeValue(Style::style,Style::background::url("icon/logo.png")+Style::background::position::center_center+Style::background::repeat::norepeat+Style::background::size::contain);
        logoCOntainer->setZIndex(105);
    }


    {
        auto navigationContainer = sRow->addWidget(cpp14::make_unique<WContainerWidget>());
        navigationContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_10+Bootstrap::Grid::Medium::col_md_10+Bootstrap::Grid::Small::col_sm_10+Bootstrap::Grid::ExtraSmall::col_xs_9);
        auto layout = navigationContainer->setLayout(cpp14::make_unique<WVBoxLayout>());



        Wt::WNavigationBar *navigation =
                layout->addWidget(Wt::cpp14::make_unique<Wt::WNavigationBar>(),0,AlignmentFlag::Justify|AlignmentFlag::Middle);
             navigation->setTitle("Serik Genç Fikir");
        navigation->setResponsive(true);


        // Setup a Left-aligned menu.
        auto leftMenu = Wt::cpp14::make_unique<Wt::WMenu>();
        auto leftMenu_ = navigation->addMenu(std::move(leftMenu));

        auto giris = leftMenu_->addItem("Genç Fikir", Wt::cpp14::make_unique<Wt::WText>("There is no better place!"));
        giris->triggered().connect([&](){
            this->_gencfikir.emit(NoClass());
        });
        leftMenu_->addItem("Ödüller", Wt::cpp14::make_unique<Wt::WText>("Layout contents"))
                ->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/?_=layout"));
        leftMenu_->addItem("Yarışma Şartnamesi");
        leftMenu_->addItem("Proje Formatı");


        // Setup a Right-aligned menu.
        auto rightMenu = Wt::cpp14::make_unique<Wt::WMenu>();
        auto rightMenu_ = navigation->addMenu(std::move(rightMenu), Wt::AlignmentFlag::Right);

        auto basvuruitem = rightMenu_->addItem(WString::fromUTF8("Başvuru"));
        basvuruitem->clicked().connect([&](){
            _Basvuru.emit(NoClass());
        });
    }

}

Header::Header::~Header()
{

}

Signal<NoClass> &Header::Header::Format()
{
    return _Format;
}

Signal<NoClass> &Header::Header::Basvuru()
{
    return  _Basvuru;
}


Signal<NoClass> &Header::Header::SartName()
{
    return _SartName;
}

Signal<NoClass> &Header::Header::mOduller()
{
    return _mOduller;
}

Signal<NoClass> &Header::Header::gencfikir()
{
    return _gencfikir;
}
