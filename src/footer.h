#ifndef FOOTER_H
#define FOOTER_H

#include <Wt/WContainerWidget.h>
#include "inlinestyle.h"
#include "bootstrap.h"
#include <Wt/WText.h>


using namespace Wt;

namespace Footer {

    class Footer : public WContainerWidget
    {
    public:
        Footer();
        virtual ~Footer();

    private:
        void initFooter();
    };

}


#endif // FOOTER_H
