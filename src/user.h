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
