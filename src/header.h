#ifndef HEADER_H
#define HEADER_H

#include <Wt/WContainerWidget.h>
#include "inlinestyle.h"
#include "bootstrap.h"

#include <Wt/WNavigationBar.h>
#include <Wt/WMenu.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPopupMenuItem.h>
#include <Wt/WVBoxLayout.h>

#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>
#include <Wt/WMessageBox.h>
#include <Wt/WLineEdit.h>


using namespace Wt;


namespace Header {

class Header : public WContainerWidget
{
public:
    Header();
    virtual ~Header();
};

}


#endif // HEADER_H
