#ifndef HEADERDIALOG_H
#define HEADERDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QStringList>

class HeaderDialog : public QDialog
{
    Q_OBJECT

public:
    HeaderDialog(QWidget *parent = 0);
    void setValues(QList<QString> *columns, QList<QString> *headers);

private:
    QList<QString> *columns;
    QList<QString> *headers;

    QHBoxLayout  *hLayout;
    QVBoxLayout  *rightLayout;
    QListWidget  *listWidget;
    QPushButton  *okButton;
    QPushButton  *cancelButton;
    QPushButton  *topButton;
    QPushButton  *upButton;
    QPushButton  *downButton;
    QPushButton  *bottomButton;
    QPushButton  *checkAllButton;
    QPushButton  *checkButton;
    QPushButton  *uncheckButton;

private slots:
    void saveChanges();
    void top();
    void up();
    void down();
    void bottom();
    void checkAll();
    void checkSelected();
    void uncheckSelected();
    void buttonState();
};

#endif // HEADERDIALOG_H
