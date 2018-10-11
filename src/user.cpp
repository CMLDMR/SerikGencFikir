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
        doc.append(kvp(tcnokey,this->getCeptel()));
    } catch (bsoncxx::exception &e) {
        std::cout << "tcnokey: " << e.what() << std::endl;
    }

    try {
        doc.append(kvp(passwordkey,this->getPassword()));
    } catch (bsoncxx::exception &e) {
        std::cout << "passwordkey: " << e.what() << std::endl;
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

