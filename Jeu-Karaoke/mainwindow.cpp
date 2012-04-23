#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->showMaximized();

    saved = false;

    // Création de la barre de menu - variables utilisées uniquement dans le constructeur - destruction nécessaire ?
    QMenuBar* barre_menu = menuBar();                                                 // Barre de menu

    // Menus déroulants
    QMenu* menu_fichier = barre_menu->addMenu(tr("&Fichier"));                        // Menu File

    // Barre d'outils
    QToolBar* barre_outils = addToolBar(tr("Fichier"));

    // Actions du menu File

    // Nouvelle partie
    a_nouvelle_partie = new QAction(QIcon(":/images/new.png"),tr("&Nouveau.."), this);     //
    a_nouvelle_partie->setShortcut(tr("Ctrl+N"));                                          // Raccourci clavier
    a_nouvelle_partie->setToolTip(tr("Nouvelle partie"));                                  // Information
    a_nouvelle_partie->setStatusTip(tr("Démarrer une nouvelle partie"));                   // Info Barre de status
    menu_fichier->addAction(a_nouvelle_partie);                                            // Ajout au menu Fichier
    barre_outils->addAction(a_nouvelle_partie);                                            // Ajout à la toolbar
    connect( a_nouvelle_partie, SIGNAL(triggered()), this, SLOT(nouvellePartie()));                 // Connection du signal au SLOT associé

    // Charger partie
    a_charger_partie = new QAction(QIcon(":/images/open.png"),tr("&Ouvrir.."), this);
    a_charger_partie->setShortcut(tr("Ctrl+O"));
    a_charger_partie->setToolTip(tr("Charger une partie"));
    a_charger_partie->setStatusTip(tr("Charger une partie précédente"));
    menu_fichier->addAction(a_charger_partie);
    barre_outils->addAction(a_charger_partie);
    connect(a_charger_partie, SIGNAL(triggered()),this, SLOT(chargerPartie()));

    // Sauver partie
    a_sauver_partie = new QAction(QIcon(":/images/save.png"),tr("&Sauver"), this);
    a_sauver_partie->setShortcut(tr("Ctrl+S"));
    a_sauver_partie->setToolTip(tr("Sauver partie"));
    a_sauver_partie->setStatusTip(tr("Sauver partie"));
    menu_fichier->addAction(a_sauver_partie);
    barre_outils->addAction(a_sauver_partie);
    connect(a_sauver_partie, SIGNAL(triggered()),this, SLOT(sauverPartie()));

    // Quit Application
    a_quitter = new QAction(QIcon(":/images/quit.png"),tr("&Quitter"), this);
    a_quitter->setShortcut(tr("Ctrl+E"));
    a_quitter->setToolTip(tr("Quitter le jeu"));
    a_quitter->setStatusTip(tr("Quitter le jeu"));
    menu_fichier->addAction(a_quitter);
    barre_outils->addAction(a_quitter);
    connect(a_quitter, SIGNAL(triggered()),this, SLOT(quitterAppli()));

    zone_centrale = new QWidget;
    zone_centrale->setAutoFillBackground(true);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::yellow);
    zone_centrale->setPalette(Pal);

    player_musique = new Panel_Musique(this);
    zone_reglages = new Panel_Boutons(this);
    zone_karaoke = new Panel_Texte(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(player_musique, 0,0,1,-1);
    layout->addWidget(zone_reglages, 1,3,3,1);
    layout->addWidget(zone_karaoke, 1,0,3,3);

    zone_centrale->setLayout(layout);
    setCentralWidget(zone_centrale);


}



MainWindow::~MainWindow()
{
    delete ui;

    delete a_nouvelle_partie;
    delete a_charger_partie;
    delete a_sauver_partie;
    delete a_quitter;

    delete player_musique;
    delete zone_reglages;
    delete zone_karaoke;
    delete zone_centrale;

}



void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void MainWindow::nouvellePartie(){
    cout << "Nouvelle partie" << endl;

}

void MainWindow::chargerPartie(){

    // Ouverture d'une boite de choix d'ouverture
    QString fileName =
            QFileDialog::getOpenFileName (this,
                                          tr("Ouvrir..."),
                                          "/desa",
                                          tr("Karaoke Game File (*.kgf)"));

    // Action à effectuer ensuite !
    cout << "Ouvrir : " << fileName.toStdString() << endl;

    zone_karaoke->charger_texte(fileName.toStdString());

}

void MainWindow::sauverPartie(){

    saved=false;

    // Ouverture d'une boite de choix de sauvegarde
    QString fileName =
            QFileDialog::getSaveFileName(this,
                                         tr("Sauver..."),
                                         "/desa",
                                         tr("Karaoke Game File (*.kgf)"));
    // Action à effectuer ensuite !
    cout << "Sauver : " << fileName.toStdString() << endl;

    // Il faudra mettre saved à true dans la méthode de sauvegarde des classes inférieures !


}

void MainWindow::quitterAppli(){

    // Création d'une message box usuelle
    QMessageBox quitter(this);
    int result = quitter.question(this,"Quitter","Voulez-vous vraiment quitter ?",QMessageBox::Yes,QMessageBox::No);

    if(result==QMessageBox::Yes){
        qApp->exit();
    }

}



void MainWindow::closeEvent(QCloseEvent *event)                      // On essaie de quitter l'appli en cliquant sur la croix
{
    int result = maybeSave();                                        // On appelle MaybeSave pour ouvrir la fenêtre de dialogue et on stoque la réponse dans result
    if (result==0)                                                   // Réponse = sauvegarder
    {
        this->sauverPartie();                                        // On appelle le slot de sauvegarde de notre fichier
        if(saved)                                                    // Si on a bien sauvé dans la seconde fenêtre et non cliqué sur annuler, on peut quitter
        {
            event->accept();
        }
        else                                                         // Sinon, on ne quitte pas
        {
            event->ignore();
        }
    }
    else if(result==1)                                               // Réponse = cancel
    {
        event->ignore();
    }
    else if(result==2)                                               // Réponse = quitter sans sauver
    {
        event->accept();
    }
}

const int MainWindow::maybeSave()                                   // Ouvre une boîte de dialogue demandant si on souhaite réellement quitter sans sauver
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("KaraoGame"),
                               tr("Voulez-vous vraiment quitter sans sauver ?"
                                  ),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)                                                           // Réponse = sauvegarder
        return 0;
    else if (ret == QMessageBox::Cancel)                                                    // Réponse = annuler
        return 1;

    return 2;                                                                               // Réponse = quitter sans sauver
}

