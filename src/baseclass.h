#ifndef BASECLASS_H
#define BASECLASS_H

#include <QtCore/qglobal.h>

#include "bsoncxx/document/element.hpp"
#include "bsoncxx/document/value.hpp"
#include "bsoncxx/document/view.hpp"
#include "bsoncxx/document/view_or_value.hpp"
#include "bsoncxx/exception/exception.hpp"
#include <bsoncxx/stdx/make_unique.hpp>

#include "bsoncxx/builder/basic/document.hpp"
#include "bsoncxx/builder/basic/array.hpp"
#include "bsoncxx/builder/basic/kvp.hpp"

#include "mongocxx/database.hpp"
#include "mongocxx/collection.hpp"
#include "mongocxx/stdx.hpp"
#include "mongocxx/exception/exception.hpp"
#include <mongocxx/gridfs/bucket.hpp>


#include "inlinestyle.h"
#include "bootstrap.h"

#include <fstream>


#include <random>

#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QIODevice>
#include <QByteArray>

using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::array;
using bsoncxx::builder::basic::kvp;

using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;




using namespace Wt;

class BaseClass
{
public:
    BaseClass(mongocxx::database* _db);



    mongocxx::database *getDb();

    mongocxx::collection collection(const std::string& collectionName);

    bsoncxx::types::value uploadfile( QString filepath );

    std::string download(bsoncxx::oid _oid , bool forceFilename = false );


private:
    mongocxx::database* db;
};





class BaseWidget : public WContainerWidget , public BaseClass
{
public:
    BaseWidget(mongocxx::database* _db);

    void sendSMS(std::string numara , std::string sms);


    enum class MessageType{
        info = 0 ,
        warning
    };

    void ShowMessage(std::string mesaj , MessageType type = MessageType::info );



};







//static bsoncxx::types::value uploadfile(mongocxx::gridfs::bucket* bucket,QString filepath )
//{
//    QFile file( filepath );
//    if( file.open(QIODevice::ReadWrite) )
//    {
//        QFileInfo info(filepath);
//        auto uploader = bucket->open_upload_stream(info.fileName().toStdString().c_str());
//        QByteArray ar = file.readAll();
//        uploader.write((std::uint8_t*)ar.data(),ar.size());
//        auto res = uploader.close();
//        file.close();
//        return res.id();
//    }
//}



//static std::string downloadifNotExist(mongocxx::gridfs::bucket* Bucket,std::string oid, bool forceFilename )
//    {




//        if( QFile::exists( QString("docroot/tempfile/%1.indexed").arg(oid.c_str()) ) )
//        {
//            QFile file(QString("docroot/tempfile/%1.indexed").arg(oid.c_str()));
//            if( file.open(QIODevice::ReadOnly) )
//            {
//                QString fileName = QString::fromUtf8(file.readAll());
//                file.close();
//                return fileName.toStdString();
//            }
//        }else{
//            std::cout << "FILE NOT FOUND" << QString("docroot/tempfile/%1.indexed").arg(oid.c_str()).toStdString() << std::endl;
//        }




//        auto doc = bsoncxx::builder::basic::document{};

//        try {
//            doc.append(bsoncxx::builder::basic::kvp("key",bsoncxx::oid{oid}));
//        } catch (bsoncxx::exception& e) {
//            std::cout << "Error: " << e.what() << std::endl;
//            return "NULL";
//        }



//        mongocxx::gridfs::downloader downloader;
//        try {
//            auto roid = bsoncxx::types::value(doc.view()["key"].get_oid());
//            downloader = Bucket->open_download_stream(roid);

//        } catch (bsoncxx::exception &e) {
//            return "img/error.png";
//        }


//        auto file_length = downloader.file_length();
//        auto bytes_counter = 0;

//        QFileInfo info( downloader.files_document()["filename"].get_utf8().value.to_string().c_str() );

//        QString fullFilename;

//        if( forceFilename )
//        {
//            fullFilename = QString("tempfile/%1").arg(downloader.files_document()["filename"].get_utf8().value.to_string().c_str());
//        }else{
//            fullFilename = QString("tempfile/%2.%1").arg(info.suffix())
//                        .arg(downloader.files_document()["md5"].get_utf8().value.to_string().c_str());
//        }

////        if( QFile::exists("docroot/"+fullFilename) )
////        {
////            return fullFilename.toStdString();
////        }

//        auto buffer_size = std::min(file_length, static_cast<std::int64_t>(downloader.chunk_size()));
//        auto buffer = bsoncxx::stdx::make_unique<std::uint8_t[]>(static_cast<std::size_t>(buffer_size));

//        std::ofstream out;

//        out.open("docroot/"+fullFilename.toStdString(),std::ios::out | std::ios::app | std::ios::binary);


//        if( out.is_open() )
//        {

//            while ( auto length_read = downloader.read(buffer.get(), static_cast<std::size_t>(buffer_size)) ) {

//                auto bufferPtr = buffer.get();
//                std::cout << "Size Of: " << sizeof (bufferPtr) << std::endl;
//                out.write(reinterpret_cast<char*>(bufferPtr),length_read);

//                bytes_counter += static_cast<std::int32_t>( length_read );
////                std::cout << "Downloaded: " << file_length << "/" << bytes_counter << " lengRead :" << length_read << " Buffer Size: " << buffer_size << std::endl;

//            }

//            out.close();
//        }

//        else{
//            std::cout << "Error Can Not Open File: " <<"docroot/"+fullFilename.toStdString() << std::endl;
//        }


//        QFile file(QString("docroot/tempfile/%1.indexed").arg(oid.c_str()));
//        if( file.open(QIODevice::ReadWrite) )
//        {
//            file.write(fullFilename.toUtf8());
//            file.close();
//        }else{
//            std::cout << "FILE CAN NOT CREATED: " << file.fileName().toStdString() << fullFilename.toStdString() << std::endl;
//        }

//        std::cout << "FILE FORCED : " << forceFilename <<" FILE FILL: " << fullFilename.toStdString() <<" TOTHIS FILE: " << file.fileName().toStdString() << std::endl;

//        return fullFilename.toStdString();

//    }



#endif // BASECLASS_H
