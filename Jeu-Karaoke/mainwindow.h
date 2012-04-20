#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QEvent>
#include <QCloseEvent>
#include <QPalette>
#include <iostream>

#include "panel_boutons.h"
#include "panel_musique.h"
#include "panel_texte.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QAction* a_nouvelle_partie;                  //Actions du menu déroulant Fichier
    QAction* a_charger_partie;
    QAction* a_sauver_partie;
    QAction* a_quitter;

    bool saved;                                  // Booléen permettant de savoir si on a vraiment sauvé après avoir ouvert une QFileDialog de sauvergarde

    QWidget* zone_centrale;

    Panel_Boutons* zone_reglages;
    Panel_Musique* player_musique;
    Panel_Texte* zone_karaoke;



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void closeEvent(QCloseEvent*);       // Fonction lancée lorsqu'on clique sur la croix


protected:
    virtual void changeEvent(QEvent *);         // Changer la langue



private:
    Ui::MainWindow *ui;
    virtual const int maybeSave();               // Fonction générant la boîte de dialogue lorsqu'on clique sur la croix (appelée par closeEvent(..))



public slots:                                    // Slots associés aux différentes QAction
    virtual void nouvellePartie();               // nouvelle partie
    virtual void chargerPartie();                // ouverture d'un fichier
    virtual void sauverPartie();                 // sauvegarde d'un fichier
    virtual void quitterAppli();                 // quitter l'application

};

#endif // MAINWINDOW_H
