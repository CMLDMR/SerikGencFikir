#include "baseclass.h"
#include <QXmlStreamWriter>
#include <QByteArray>
#include <QString>
#include "bsoncxx/json.hpp"

#include <Wt/Http/Client.h>

BaseClass::BaseClass(mongocxx::database *_db)
    :db(_db)
{

}



mongocxx::database *BaseClass::getDb()
{
    return db;
}

mongocxx::collection BaseClass::collection(const std::string &collectionName)
{
    return this->db->collection(collectionName);
}

bsoncxx::types::value BaseClass::uploadfile(QString filepath)
{
    auto bucket = this->getDb()->gridfs_bucket();
    QFile file( filepath );
    if( file.open(QIODevice::ReadWrite) )
    {
        QFileInfo info(filepath);
        auto uploader = bucket.open_upload_stream(info.fileName().toStdString().c_str());
        QByteArray ar = file.readAll();
        uploader.write((std::uint8_t*)ar.data(),ar.size());
        auto res = uploader.close();
        file.close();
        return res.id();
    }
}

std::string BaseClass::download(bsoncxx::oid _oid, bool forceFilename)
{

    std::string oid = _oid.to_string();

    if( QFile::exists( QString("docroot/tempfile/%1.indexed").arg(oid.c_str()) ) )
    {
        QFile file(QString("docroot/tempfile/%1.indexed").arg(oid.c_str()));
        if( file.open(QIODevice::ReadOnly) )
        {
            QString fileName = QString::fromUtf8(file.readAll());
            file.close();
            return fileName.toStdString();
        }
    }else{
        std::cout << "FILE NOT FOUND: " << QString("docroot/tempfile/%1.indexed").arg(oid.c_str()).toStdString() << std::endl;
    }




    auto doc = bsoncxx::builder::basic::document{};

    try {
        doc.append(bsoncxx::builder::basic::kvp("key",bsoncxx::oid{oid}));
    } catch (bsoncxx::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return "NULL";
    }

    std::cout << "doc file" << std::endl;



    auto Bucket = this->getDb()->gridfs_bucket();
    mongocxx::gridfs::downloader downloader;
    bsoncxx::types::value roid(doc.view()["key"].get_oid());


    try {
        downloader = Bucket.open_download_stream(roid);
    } catch (mongocxx::exception &e) {
        std::cout << "Download Error: " << e.what() << std::endl;
        return "icon/error.png";
    }

    std::cout << "openfile file" << std::endl;


    auto file_length = downloader.file_length();
    auto bytes_counter = 0;

    std::cout << "filename exracting..." << std::endl;


    std::cout << bsoncxx::to_json(downloader.files_document()) << std::endl;


    QFileInfo info;

    try {
        info.setFile( downloader.files_document()["filename"].get_utf8().value.to_string().c_str() );
    } catch (bsoncxx::exception &e) {
        std::cout << "grid fs Error: " << e.what() << std::endl;
    }



    std::cout << "filename exracting..." << std::endl;


    QString fullFilename;

    if( forceFilename )
    {
        fullFilename = QString("tempfile/%1").arg(downloader.files_document()["filename"].get_utf8().value.to_string().c_str());
    }else{
        fullFilename = QString("tempfile/%2.%1").arg(info.suffix())
                    .arg(downloader.files_document()["_id"].get_oid().value.to_string().c_str());
    }

    std::cout << "file Downloaded Path: "<<fullFilename.toStdString() << std::endl;

    if( QFile::exists("docroot/"+fullFilename) )
    {
        return fullFilename.toStdString();
    }

    auto buffer_size = std::min(file_length, static_cast<std::int64_t>(downloader.chunk_size()));
    auto buffer = bsoncxx::stdx::make_unique<std::uint8_t[]>(static_cast<std::size_t>(buffer_size));

    std::ofstream out;

    out.open("docroot/"+fullFilename.toStdString(),std::ios::out | std::ios::app | std::ios::binary);


    if( out.is_open() )
    {

        while ( auto length_read = downloader.read(buffer.get(), static_cast<std::size_t>(buffer_size)) ) {

            auto bufferPtr = buffer.get();
            std::cout << "Size Of: " << sizeof (bufferPtr) << std::endl;
            out.write(reinterpret_cast<char*>(bufferPtr),length_read);

            bytes_counter += static_cast<std::int32_t>( length_read );
//                std::cout << "Downloaded: " << file_length << "/" << bytes_counter << " lengRead :" << length_read << " Buffer Size: " << buffer_size << std::endl;

        }

        out.close();
    }

    else{
        std::cout << "Error Can Not Open File: " <<"docroot/"+fullFilename.toStdString() << std::endl;
    }


    QFile file(QString("docroot/tempfile/%1.indexed").arg(oid.c_str()));
    if( file.open(QIODevice::ReadWrite) )
    {
        file.write(fullFilename.toUtf8());
        file.close();
    }else{
        std::cout << "FILE CAN NOT CREATED: " << file.fileName().toStdString() << fullFilename.toStdString() << std::endl;
    }

    std::cout << "FILE FORCED : " << forceFilename <<" FILE FILL: " << fullFilename.toStdString() <<" TOTHIS FILE: " << file.fileName().toStdString() << std::endl;

    return fullFilename.toStdString();
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
        std::cout << "HTTP DONE: " << code.message().c_str() << " - " << message.body().c_str() << " - " << numara << " - " << sms << std::endl;
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
