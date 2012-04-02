#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QAction* a_nouvelle_partie;                    //Actions du menu déroulant Fichier
    QAction* a_charger_partie;
    QAction* a_sauver_partie;
    QAction* a_quitter;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:                                    // Slots associés aux différentes QAction
    virtual void nouvellePartie();               // nouvelle partie
    virtual void chargerPartie();                // ouverture d'un fichier
    virtual void sauverPartie();                 // sauvegarde d'un fichier
    virtual void quitterAppli();                 // quitter l'application

};

#endif // MAINWINDOW_H
