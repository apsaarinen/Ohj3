#ifndef BEGINDIALOG_HH
#define BEGINDIALOG_HH

#include "core/basicresources.h"
#include <QDialog>

namespace Ui {
class begindialog;
}

class begindialog : public QDialog
{
    Q_OBJECT

public:
    explicit begindialog(QWidget *parent = 0);
    ~begindialog();


    std::vector<std::string> getPlayernames();

    Course::ResourceMap getStartingResources();

    int getResourcesToWin();


private:
    Ui::begindialog *ui;
};

#endif // BEGINDIALOG_HH
