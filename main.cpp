
#include "mainapplication.h"
#include "mongocxx/instance.hpp"




int main(int argc, char *argv[])
{



    mongocxx::instance();


    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
      /*
       * You could read information from the environment to decide whether
       * the user has permission to start a new application
       */
      return Wt::cpp14::make_unique<MainApplication>(env);
    });

}
