#include "user.h"

User::User()
{

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

std::string User::getUniversite() const
{
    return universite;
}

void User::setUniversite(const std::string &value)
{
    universite = value;
}

