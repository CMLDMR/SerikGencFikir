#ifndef PROJECT_H
#define PROJECT_H

#include <QtCore/qglobal.h>
#include "baseclass.h"
#include "user.h"

class Project : public BaseWidget , public User
{
public:
    Project(mongocxx::database* _db , User user);


private:
    WContainerWidget* mTitleContainer;
    void initTitleContainer();


    WContainerWidget* mListContainer;
    void initProjectList();

    WContainerWidget* mController;
    void initController();

    WContainerWidget* mNewContainer;
    void initNewProject();

    std::string clientFileName;
    std::string uploadedfilefullpath;

    WLineEdit* mProjectName;
    WComboBox* mKategori;
};

#endif // PROJECT_H
