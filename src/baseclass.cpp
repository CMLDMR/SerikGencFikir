#include "baseclass.h"
#include <QXmlStreamWriter>
#include <QByteArray>
#include <QString>

#include <Wt/Http/Client.h>

BaseClass::BaseClass(mongocxx::database *_db)
    :db(_db)
{

}

mongocxx::database *BaseClass::getDb()
{
    return db;
}



BaseWidget::BaseWidget(mongocxx::database *_db)
    :WContainerWidget () , BaseClass (_db)
{

}


void BaseWidget::sendSMS(std::string numara, std::string sms)
{
    QByteArray ar;

    ar.clear();

    QXmlStreamWriter stream(&ar);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    stream.writeStartElement("MainmsgBody");

    stream.writeTextElement("Command", "0");
    stream.writeTextElement("PlatformID", "1");
    stream.writeTextElement("ChannelCode", "474");
    stream.writeTextElement("UserName", "serikbel");
    stream.writeTextElement("PassWord", "nisan2012");
    stream.writeTextElement("Mesgbody", sms.c_str() );
    stream.writeTextElement("Numbers", numara.c_str() );
    stream.writeTextElement("Type", "1");
    stream.writeTextElement("Concat", "1");
    stream.writeTextElement("Originator", "SERiK BLD");

    stream.writeEndElement();

    stream.writeEndDocument();

    auto httpclient = addChild(std::make_unique<Http::Client>());

    Http::Message msg;
    msg.setHeader("Content-Type","application/json");

    msg.addBodyText(ar.toStdString());

    httpclient->setSslCertificateVerificationEnabled(false);

    httpclient->done().connect([=](AsioWrapper::error_code code, Http::Message message){
        std::cout << "HTTP DONE: " << code.message().c_str() << message.body().c_str() << std::endl;

    });

    httpclient->post("http://processor.smsorigin.com/xml/process.aspx",msg);
}

void BaseWidget::ShowMessage(std::string mesaj, MessageType type)
{


    std::string title;

    if( type == MessageType::info )
    {
        title = "Bilgi";
    }

    if( type == MessageType::warning )
    {
        title = "Uyarı";
    }

    auto dialog = addChild(Wt::cpp14::make_unique<Wt::WDialog>(title));

    dialog->contents()->addWidget(Wt::cpp14::make_unique<WText>(mesaj.c_str()));

    dialog->contents()->addStyleClass("form-group");



    Wt::WPushButton *ok =
            dialog->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Tamam"));
    ok->setDefault(true);






    /*
     * Accept the dialog
     */
    ok->clicked().connect([=] {
        dialog->accept();

    });


    /*
     * Process the dialog result.
     */
    dialog->finished().connect([=] {
        removeChild(dialog);
    });

    dialog->show();

}
