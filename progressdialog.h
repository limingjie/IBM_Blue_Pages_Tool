#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QtGui>

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    ProgressDialog(QWidget *parent = 0);

private:
    QVBoxLayout      *vLayout;
    QLabel           *searchLabel;
    QLabel           *progressLabel;
    QProgressBar     *currentProgress;
    QProgressBar     *overallProgress;
    QDialogButtonBox *buttonBox;

    size_t total;

public:
    void setText(QString text);
    void increase(int increase);
    void setOverallProgress(int done, int total);

public slots:
    void setCurrentProgress(int done, int total);
};

#endif // PROGRESSDIALOG_H
