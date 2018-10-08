#include "mainapplication.h"



MainApplication::MainApplication(const WEnvironment &env)
    :WApplication(env)
{
    auto container = root()->addWidget(cpp14::make_unique<WContainerWidget>());

    container->setContentAlignment(AlignmentFlag::Center);


    container->setHeight(100);

    container->addWidget(cpp14::make_unique<WText>("Hello World From Serik Genç Fikir"));


}
