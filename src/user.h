#ifndef USER_H
#define USER_H

#include <string.h>
#include <iostream>

using namespace std;
class User
{
public:
    User();

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

    std::string getUniversite() const;
    void setUniversite(const std::string &value);

private:
    std::string adsoyad;
    std::string ceptel;
    std::string universite;
    std::string addres;
    std::string tcno;
    std::string password;
};



#endif // USER_H
