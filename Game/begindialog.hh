#ifndef BEGINDIALOG_HH
#define BEGINDIALOG_HH

#include "core/basicresources.h"
#include <QDialog>

namespace Ui {
/**
 * @brief Begindialog class shows pop-up window in the beginning of the game. Asks \n
 * for player names, amount of starting resources and amount of resources to win.
 */
class begindialog;
}

class begindialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the class
     * @param parent can be used to point to a parent widget. Not used.
     */
    explicit begindialog(QWidget *parent = 0);
    ~begindialog();

    /**
     * @brief getPlayernames Returns players names.
     * @return Vector of containing both player names.
     */
    std::vector<std::string> getPlayernames();

    /**
     * @brief getStartingResources Returns amount of starting resources.
     * @return ResourceMap containing amounts of resources.
     */
    Course::ResourceMap getStartingResources();

    /**
     * @brief getResourcesToWin Returns amount of resources needed for a win.
     * @return Amount of resources needed for a win.
     */
    int getResourcesToWin();


private:
    Ui::begindialog *ui;
};

#endif // BEGINDIALOG_HH
