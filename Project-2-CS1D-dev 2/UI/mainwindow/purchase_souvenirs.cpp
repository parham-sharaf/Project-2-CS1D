#include "purchase_souvenirs.h"
#include "ui_purchase_souvenirs.h"
#include <QVector>
#include "../mainwindow/display_purchases.h"


purchase_souvenirs::purchase_souvenirs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::purchase_souvenirs)
{
    ui->setupUi(this);

    teams.push_back("Boston Celtics");
    teams.push_back("Chicago Bulls");
    teams.push_back("New York Knicks");

    // create new table for Purchases
    login conn;
    conn.connOpen();
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS Purchases (purchaseTeam VARCHAR(50), purchaseSouvenir VARCHAR(50), purchasePrice VARCHAR(50), purchaseQuan VARCHAR(50), totalTeam VARCHAR(50), totalSpent VARCHAR(50), totalSouv VARCHAR(50))");
    query.exec();

    conn.connClose();

    display_souvenirs();
}

purchase_souvenirs::~purchase_souvenirs()
{
    delete ui;
}

void purchase_souvenirs::on_purchase_souvenirs_2_clicked()
{
    QString teamName = teams.front();   //current team being visited
    QString souvenir = ui->comboBox_souvenirs->currentText();
    QString quantityString = ui->spinBox_souvenirs->text();
    //int quantity = quantityString.toInt();
    QString priceString;
    //QString price;

     // assign variable for the price of the selected souvenir
    login conn1;
    conn1.connOpen();
    QSqlQuery query1;

    query1.exec("select * from Souvenirs where SouvenirName = '"+souvenir+"' AND TeamName = '"+teamName+"'");

    while(query1.next())
    {
        priceString = query1.value(2).toString();
    }

    conn1.connClose();
    // qDebug to verify values
    //qDebug() << teamName << souvenir << price << quantity;

    // pass variables to add to the Purchases database
    addToDatabase(teamName, souvenir, priceString, quantityString);
}

void purchase_souvenirs::display_souvenirs()
{
    if (teams.empty())
    {
        ui->current_team->setText("You have completed your trip!");
        return;
    }

    // this function handles the souvenirs display and purchasing of souvenirs
    QString teamName = teams.front();

    ui->current_team->setText(teamName);

    login conn;
    conn.connOpen();
    QSqlQueryModel *modal = new QSqlQueryModel;
    QSqlQuery* qry = new QSqlQuery(conn.informationDb);
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Souvenir"));
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("Price"));

    qry->prepare("SELECT SouvenirName, Price from Souvenirs where TeamName='"+teamName+"'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_souvenirs->setModel(modal);
    conn.connClose();


    login conn2;
    QSqlQueryModel *modal2 = new QSqlQueryModel();

    conn2.connOpen();

    QSqlQuery* qry2 = new QSqlQuery(conn2.informationDb);

    qry2->exec("select SouvenirName FROM Souvenirs where TeamName='"+teamName+"'");

    //qry->exec();
    modal2->setQuery(*qry2);
    ui->comboBox_souvenirs->setModel(modal2);

    conn2.connClose();
}

void purchase_souvenirs::on_next_team_clicked()
{
    QString localTotalString =QString::number(localTotal);
    QString localSuvString = QString::number(localNumSouv);
    QString teamName = teams.front();   // looks at last team used

    qDebug() << "Checking local variables" << localTotalString << localSuvString;

    teams.pop_front();      // move to next team

    login conn;
    conn.connOpen();

    QSqlQuery query;
    query.prepare("INSERT INTO Purchases(totalTeam, totalSpent, totalSouv) VALUES('"+teamName+"','"+localTotalString+"','"+localSuvString+"')");
    if (!query.exec())
        qDebug() << "Values not added! Error!";
    else
        qDebug() << "Values added to Purchases database";

    conn.connClose();

    // set local # of souvenirs and local total price to 0
    localNumSouv = 0;
    localTotal = 0;

    // set display back to $0
    ui->label_spent_local->setNum(localTotal);

    // add the quantity total and price total
    display_souvenirs();
}

void purchase_souvenirs::on_end_trip_clicked()
{
    // delete purchase columns from database
    login conn;
    conn.connOpen();

    QSqlQuery query;
    query.prepare("DROP TABLE purchases");
    query.exec();

    conn.connClose();
}

void purchase_souvenirs::addToDatabase(QString teamName, QString souvenir, QString price, QString quantity)
{
    // place purchased souvenirs into database
    login conn;
    conn.connOpen();
    double priceDouble;
    int quantityInt;
    double total = 0;
    QString totalString;

    priceDouble = price.toDouble();
    quantityInt = quantity.toInt();

    total = priceDouble*quantityInt;

    localNumSouv+=quantityInt;
    localTotal+=total;
    grandTotal+=total;


        ui->label_spent_local->setNum('$' + localTotal);
        ui->label_totalEverywhere->setNum('$' + grandTotal);

        qDebug() << "The grand total is " << grandTotal;

        qDebug() << teamName << souvenir << price << quantity;

    if (quantityInt != 0)
    {
     QSqlQuery query;
     query.prepare("INSERT INTO Purchases(purchaseTeam, purchaseSouvenir, purchasePrice, purchaseQuan) VALUES('"+teamName+"','"+souvenir+"','"+price+"', '"+quantity+"')");
     if (!query.exec())
        qDebug() << "Values not added! Error!";
      else
         qDebug() << "Values added to Purchases database";

        conn.connClose();

    // display purchases
    login conn2;
    conn2.connOpen();
    QSqlQueryModel *modal2 = new QSqlQueryModel;
    QSqlQuery* qry2 = new QSqlQuery(conn.informationDb);
    modal2->setHeaderData(0, Qt::Horizontal, QObject::tr("Souvenir"));
    modal2->setHeaderData(0, Qt::Horizontal, QObject::tr("Price"));

    qry2->prepare("SELECT purchaseSouvenir, purchaseQuan from Purchases where purchaseTeam = '"+teamName+"'");
    qry2->exec();
    modal2->setQuery(*qry2);
    ui->tableView_purchased->setModel(modal2);


    conn2.connClose();
    }
    else
        return;
}

void purchase_souvenirs::on_pushButton_view_receipt_clicked()
{
    display_purchases receipt;
    receipt.setModal(true);
    receipt.exec();
}