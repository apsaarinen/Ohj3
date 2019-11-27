#ifndef ENDDIALOG_HH
#define ENDDIALOG_HH

#include "player.h"

#include <QDialog>

namespace Ui {

/**
 * @brief Endialog class shows pop-up window announcing the result when game ends.
 *
 * Has text label for game result and exit button for quitting the game.
 */
class enddialog;
}

class enddialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the class
     * @param parent can be used to point to a parent widget. Not used.
     */
    explicit enddialog(QWidget *parent = 0);
    ~enddialog();

    /**
     * @brief setWinner Announces winner or a draw in the end of the game.
     * @param winners Pointer to vector which has winner or winners.
     * @param round Number of rounds played.
     */
    void setWinner(std::vector<std::shared_ptr<Player> > winners, int round);

private:
    Ui::enddialog *ui;
};

#endif // ENDDIALOG_HH
