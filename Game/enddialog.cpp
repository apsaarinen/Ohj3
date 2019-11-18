#include "enddialog.hh"
#include "ui_enddialog.h"

enddialog::enddialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enddialog)
{
    ui->setupUi(this);
}

enddialog::~enddialog()
{
    delete ui;
}

void enddialog::setWinner(std::vector<std::shared_ptr<Player> > winners)
{
    if(winners.size() == 1) {
            // One winner
    QString winnerText = QString::fromStdString(winners[0]->getName()) +
            " has won the game!";
    ui->label_result->setText(winnerText);
    } else {
        // Draw
        ui->label_result->setText("It's a draw!");
    }
}
