#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WText.h>

#include "src/header.h"
#include "src/body.h"
#include "src/footer.h"


#include "mongocxx/client.hpp"


using namespace Wt;

class MainApplication : public WApplication
{
public:
    MainApplication(const Wt::WEnvironment& env);

    std::shared_ptr<Wt::WBootstrapTheme> p_wtTheme;

    Header::Header* header;
    Body::Body* body;
    Footer::Footer* footer;


    mongocxx::client* mClient;
    mongocxx::database db;
};

#endif // MAINAPPLICATION_H
