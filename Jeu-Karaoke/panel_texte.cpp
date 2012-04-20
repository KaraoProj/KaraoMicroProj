#include "panel_texte.h"

Panel_Texte::Panel_Texte(QWidget *parent) :
    QWidget(parent)
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::green);
    setPalette(Pal);
    setAutoFillBackground(true);
}
