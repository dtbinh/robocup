#include "GameInformationDisplayWidget.h"
#include "Infrastructure/GameInformation/GameInformation.h"
#include <sstream>

GameInformationDisplayWidget::GameInformationDisplayWidget(QWidget *parent) :
    QTextBrowser(parent)
{
}

void GameInformationDisplayWidget::setGameInfoData(const GameInformation* newGameInfoData)
{
    QString displayText(newGameInfoData->toString().c_str());
    this->setText(displayText);
}
