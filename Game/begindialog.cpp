#include "begindialog.hh"
#include "ui_begindialog.h"

begindialog::begindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::begindialog)
{
    ui->setupUi(this);
}

begindialog::~begindialog()
{
    delete ui;
}

std::vector<std::string> begindialog::getPlayernames()
{
    std::vector<std::string> playernames;
    playernames.push_back(ui->lineEdit->text().toStdString());
    playernames.push_back(ui->lineEdit_2->text().toStdString());

    return playernames;
}

Course::ResourceMap begindialog::getStartingResources()
{
    Course::ResourceMap startResources = {
        {Course::BasicResource::MONEY, ui->spinBox_money->value()},
        {Course::BasicResource::FOOD, ui->spinBox_food->value()},
        {Course::BasicResource::WOOD, ui->spinBox_wood->value()},
        {Course::BasicResource::STONE, ui->spinBox_stone->value()},
        {Course::BasicResource::ORE, ui->spinBox_ore->value()},
    };

    return startResources;
}

int begindialog::getResourcesToWin()
{
    return ui->spinBox_resourcestowin->value();
}
