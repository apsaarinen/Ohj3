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

void enddialog::setWinner(std::vector<std::shared_ptr<Game::Player> > winners, int round)
{
    if(winners.size() == 1) {
        // One winner, calculate sum of resources
        Course::ResourceMap playerResourceMap = winners[0]->getResources();
        int resourceSum = 0;
        for(auto n: playerResourceMap) {
            resourceSum += n.second;
        }
        QString winnerText = QString::fromStdString(winners[0]->getName()) +
                " has won the game with " + QString::number(resourceSum) +
                " resources in " + QString::number(round) + " rounds!";
        ui->label_result->setText(winnerText);
    } else {
        // Draw
        ui->label_result->setText("It's a draw in " + QString::number(round) + " rounds!");
    }
}
