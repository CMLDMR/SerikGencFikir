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
#include <Wt/WSignal.h>

using namespace Wt;


namespace Header {

class Header : public WContainerWidget
{
public:
    Header();
    virtual ~Header();


    Signal<NoClass> &gencfikir();

    Signal<NoClass> &mOduller();

    Signal<NoClass> &SartName();

    Signal<NoClass> &Format();

private:


    Signal<NoClass> _gencfikir;
    Signal<NoClass> _mOduller;
    Signal<NoClass> _SartName;
    Signal<NoClass> _Format;
    Signal<NoClass> _Basvuru;


};

}


#endif // HEADER_H
