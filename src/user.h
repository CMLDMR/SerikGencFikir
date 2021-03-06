#ifndef USER_H
#define USER_H

#include <string.h>
#include <iostream>


#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/types/value.hpp>
#include <bsoncxx/types.hpp>
#include "bsoncxx/document/element.hpp"
#include "bsoncxx/document/value.hpp"
#include "bsoncxx/document/view.hpp"
#include "bsoncxx/document/view_or_value.hpp"
#include "bsoncxx/json.hpp"


using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::array;
using bsoncxx::builder::basic::kvp;

using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

using namespace std;


class User
{
public:
    User();
    User(const User& user);
    User(const User* user);
    User(bsoncxx::document::view userView);

    void setFromView(bsoncxx::document::view userView);

    User getUser() const;

    std::string getAdsoyad() const;
    void setAdsoyad(const std::string &value);

    std::string getCeptel() const;
    void setCeptel(const std::string &value);


    std::string getAddres() const;
    void setAddres(const std::string &value);

    std::string getTcno() const;
    void setTcno(const std::string &value);

    std::string getPassword() const;
    void setPassword(const std::string &value);

    bool isValid() const;

    document getDocument();
    void setDocument(const document& userDocument);

    std::string getUniversite() const;
    void setUniversite(const std::string &value);

    bsoncxx::oid getFotoOid() const;

    bsoncxx::oid getKimlikOid() const;




public:


    const std::string collection{"Users"};

    const std::string adsoyadkey{"adsoyad"};
    const std::string ceptelkey{"ceptelkey"};
    const std::string universitekey{"universitekey"};
    const std::string addreskey{"addreskey"};
    const std::string tcnokey{"tcnokey"};
    const std::string passwordkey{"passwordkey"};



    std::string getFotoid() const;
    void setFotoid(const std::string &value);

    std::string getKimlikoid() const;
    void setKimlikoid(const std::string &value);

private:
    std::string adsoyad;
    std::string ceptel;
    std::string universite;
    std::string addres;
    std::string tcno;
    std::string password;
    std::string fotoid;

    std::string kimlikoid;


    document userDoc;





};



#endif // USER_H
