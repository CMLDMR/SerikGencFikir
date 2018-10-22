#include "mainapplication.h"

#include "inlinestyle.h"

#include "../url.h"

#include "mongocxx/exception/authentication_exception.hpp"

#include "bsoncxx/builder/basic/document.hpp"
#include "bsoncxx/builder/basic/kvp.hpp"
#include "bsoncxx/builder/basic/array.hpp"
#include "bsoncxx/oid.hpp"
#include "bsoncxx/document/element.hpp"
#include "bsoncxx/array/element.hpp"
#include "bsoncxx/types.hpp"
#include "bsoncxx/json.hpp"
#include "bsoncxx/exception/exception.hpp"









MainApplication::MainApplication(const WEnvironment &env)
    :WApplication(env)
{

    try {
        mClient = new mongocxx::client(mongocxx::uri(_url));
    } catch (mongocxx::exception &e) {
        std::cout << "Connection Error: " << e.what() << std::endl;
        root()->addWidget(cpp14::make_unique<WText>("Uygulama Geçici Olarak Durduruldu."));
        return;
    }

    if( mClient->operator bool() )
    {
        std::cout << "Connected Successfully" << std::endl;
    }else{
        std::cout << "Connection is Lost" << std::endl;
        root()->addWidget(cpp14::make_unique<WText>("Uygulama Geçici Olarak Durduruldu."));
        return;
    }


    db = mClient->database(_dbname);


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

    body = root()->addWidget(cpp14::make_unique<Body::Body>(&db));


    header->gencfikir().connect(body,&Body::Body::gencFikirInit);

    header->Basvuru().connect(body,&Body::Body::BasvuruInit);

    header->SartName().connect(body,&Body::Body::Sartnameinit);

    header->Format().connect(body,&Body::Body::ProjeFormat);

    footer = root()->addWidget(cpp14::make_unique<Footer::Footer>());

    header->setZIndex(10);
    body->setZIndex(-10);


}
