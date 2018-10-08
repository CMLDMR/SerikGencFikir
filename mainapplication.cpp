#include "mainapplication.h"

#include "inlinestyle.h"



MainApplication::MainApplication(const WEnvironment &env)
    :WApplication(env)
{

    root()->setMargin(0,AllSides);

    p_wtTheme = std::make_shared<Wt::WBootstrapTheme>();
    p_wtTheme->setVersion(Wt::WBootstrapTheme::Version::v3);
    p_wtTheme->setResponsive(true);
    Wt::WApplication::instance()->setTheme(p_wtTheme);
    Wt::WApplication::instance()->setTitle("Serik Genç Fikir V2 - Üniversite");

    Wt::WApplication::instance()->useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");

    WApplication::instance()->addMetaHeader("viewport","width=device-width, initial-scale=1.0");
    this->useStyleSheet("css/css.css");

    header = root()->addWidget(cpp14::make_unique<Header::Header>());
    header->addStyleClass("headerShadow");

    body = root()->addWidget(cpp14::make_unique<Body::Body>());

    header->gencfikir().connect(body,&Body::Body::gencFikirInit);


}
