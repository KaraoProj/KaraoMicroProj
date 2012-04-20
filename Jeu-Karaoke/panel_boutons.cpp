#include "panel_boutons.h"

Panel_Boutons::Panel_Boutons(QWidget *parent) :
    QWidget(parent)
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::red);
    setPalette(Pal);
    setAutoFillBackground(true);
}
