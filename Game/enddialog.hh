#ifndef ENDDIALOG_HH
#define ENDDIALOG_HH

#include "player.h"

#include <QDialog>

namespace Ui {
class enddialog;
}

class enddialog : public QDialog
{
    Q_OBJECT

public:
    explicit enddialog(QWidget *parent = 0);
    ~enddialog();

    void setWinner(std::vector<std::shared_ptr<Player> > winners, int round);

private:
    Ui::enddialog *ui;
};

#endif // ENDDIALOG_HH
