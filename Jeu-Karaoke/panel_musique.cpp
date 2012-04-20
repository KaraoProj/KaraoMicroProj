#include "panel_musique.h"

Panel_Musique::Panel_Musique(QWidget *parent) :
    QWidget(parent)
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::blue);
    setPalette(Pal);
    setAutoFillBackground(true);
}
