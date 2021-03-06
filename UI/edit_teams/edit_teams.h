#ifndef EDIT_TEAMS_H
#define EDIT_TEAMS_H

#include <QDialog>
#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>

#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QFileInfo>
static bool isNewTeamAdded;

namespace Ui
{
    class edit_teams;
}

class edit_teams : public QDialog
{
Q_OBJECT

public:
    explicit edit_teams(QWidget *parent = nullptr);
    ~edit_teams();

private slots:
    void on_city_clicked();

    void on_load_teams_button_clicked();

    void on_load_table_button_clicked();

    void on_revert_changes_button_clicked();

//    void on_teamCombo_activated(const QString &arg1);
//
//    void on_arenaCapacity_activated(const QString &arg1);
//
//    void on_pushButton_clicked();

    void on_teamCombo_currentIndexChanged(const QString &arg1);

    void on_arenaCombo_currentTextChanged(const QString &arg1);

    void on_changeArenaButton_clicked();

private:
    Ui::edit_teams *ui;
    QString teamName;
    QString arenaName;
    int capacity{};
};

#endif // EDIT_TEAMS_H
