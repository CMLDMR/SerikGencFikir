#include "user.h"

User::User()
    :userDoc(document{})
{
    userDoc.clear();

}

User::User(const User &user)
{

    this->setAddres(user.getAddres());
    this->setAdsoyad(user.getAdsoyad());
    this->setCeptel(user.getCeptel());
    this->setPassword(user.getPassword());
    this->setTcno(user.getTcno());
    this->setUniversite(user.getUniversite());
    this->setFotoid(user.getFotoid());
    this->setKimlikoid(user.getKimlikoid());

}

User::User(const User *user)
{
    this->setAddres(user->getAddres());
    this->setAdsoyad(user->getAdsoyad());
    this->setCeptel(user->getCeptel());
    this->setPassword(user->getPassword());
    this->setTcno(user->getTcno());
    this->setUniversite(user->getUniversite());
    this->setFotoid(user->getFotoid());
    this->setKimlikoid(user->getKimlikoid());
}

User::User(bsoncxx::document::view userView)
{
    this->setAddres(userView["addreskey"].get_utf8().value.to_string());
    this->setAdsoyad(userView["adsoyad"].get_utf8().value.to_string());
    this->setCeptel(userView["ceptelkey"].get_utf8().value.to_string());
    this->setPassword(userView["passwordkey"].get_utf8().value.to_string());
    this->setTcno(userView["tcnokey"].get_utf8().value.to_string());
    this->setUniversite(userView["universitekey"].get_utf8().value.to_string());

    try {
        this->setKimlikoid(userView["kimlik"].get_oid().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "Foto Exract View Error: " << e.what() << std::endl;
    }

    try {
        this->setFotoid(userView["foto"].get_oid().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "Foto Exract Error: " << e.what() << std::endl;
    }
}

void User::setFromView(bsoncxx::document::view userView)
{
    this->setAddres(userView["addreskey"].get_utf8().value.to_string());
    this->setAdsoyad(userView["adsoyad"].get_utf8().value.to_string());
    this->setCeptel(userView["ceptelkey"].get_utf8().value.to_string());
    this->setPassword(userView["passwordkey"].get_utf8().value.to_string());
    this->setTcno(userView["tcnokey"].get_utf8().value.to_string());
    this->setUniversite(userView["universitekey"].get_utf8().value.to_string());

    try {
        this->setFotoid(userView["foto"].get_oid().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "Foto Exract View Error: " << e.what() << std::endl;
    }

    try {
        this->setKimlikoid(userView["kimlik"].get_oid().value.to_string());
    } catch (bsoncxx::exception &e) {
        std::cout << "Foto Exract View Error: " << e.what() << std::endl;
    }

}

User User::getUser() const
{
    return *this;
}

std::string User::getAdsoyad() const
{
    return adsoyad;
}

void User::setAdsoyad(const std::string &value)
{
    adsoyad = value;
}

std::string User::getCeptel() const
{
    return ceptel;
}

void User::setCeptel(const std::string &value)
{
    ceptel = value;
}


std::string User::getAddres() const
{
    return addres;
}

void User::setAddres(const std::string &value)
{
    addres = value;
}

std::string User::getTcno() const
{
    return tcno;
}

void User::setTcno(const std::string &value)
{
    tcno = value;
}

std::string User::getPassword() const
{
    return password;
}

void User::setPassword(const std::string &value)
{
    password = value;
}

bool User::isValid() const
{
    bool valid = true;

    if( tcno.length() == 0 )
    {
        valid = false;
    }

    if( adsoyad.length() == 0 )
    {
        valid = false;
    }

    if( ceptel.length() != 11 )
    {
        valid = false;
    }

    if( addres.length() == 0 )
    {
        valid = false;
    }

    if( password.length() == 0 )
    {
        valid = false;
    }

    if( universite.length() == 0 )
    {
        valid = false;
    }
    return valid;
}

bsoncxx::builder::basic::document User::getDocument()
{
    auto doc = document{};


    try {
        doc.append(kvp(adsoyadkey,this->getAdsoyad()));
    } catch (bsoncxx::exception &e) {
        std::cout << "adsoyadkey: " << e.what() << std::endl;
    }

    try {
        doc.append(kvp(ceptelkey,this->getCeptel()));
    } catch (bsoncxx::exception &e) {
        std::cout << "ceptelkey: " << e.what() << std::endl;
    }

    try {
        doc.append(kvp(universitekey,this->getUniversite()));
    } catch (bsoncxx::exception &e) {
        std::cout << "universitekey: " << e.what() << std::endl;
    }

    try {
        doc.append(kvp(addreskey,this->getAddres()));
    } catch (bsoncxx::exception &e) {
        std::cout << "addreskey: " << e.what() << std::endl;
    }

    try {
        doc.append(kvp(tcnokey,this->getTcno()));
    } catch (bsoncxx::exception &e) {
        std::cout << "tcnokey: " << e.what() << std::endl;
    }

    try {
        doc.append(kvp(passwordkey,this->getPassword()));
    } catch (bsoncxx::exception &e) {
        std::cout << "passwordkey: " << e.what() << std::endl;
    }

    try {
        doc.append(kvp("foto",this->getFotoOid()));
    } catch (bsoncxx::exception &e) {
        std::cout << "passwordkey: " << e.what() << std::endl;
    }

    try {
        doc.append(kvp("kimlik",this->getKimlikOid()));
    } catch (bsoncxx::exception &e) {
        std::cout << "kimlik: " << e.what() << std::endl;
    }
    return doc;
}

void User::setDocument(const bsoncxx::builder::basic::document &userDocument)
{

    userDoc.clear();

    for( auto element : userDocument.view() )
    {
        userDoc.append(kvp(element.key(),element.get_value()));
    }

}

std::string User::getUniversite() const
{
    return universite;
}

void User::setUniversite(const std::string &value)
{
    universite = value;
}

bsoncxx::oid User::getFotoOid() const
{
    return bsoncxx::oid(this->getFotoid());
}

bsoncxx::oid User::getKimlikOid() const
{
    return bsoncxx::oid(this->getKimlikoid());
}

std::string User::getFotoid() const
{
    return fotoid;
}

void User::setFotoid(const std::string &value)
{
    fotoid = value;
}

std::string User::getKimlikoid() const
{
    return kimlikoid;
}

void User::setKimlikoid(const std::string &value)
{
    kimlikoid = value;
}

