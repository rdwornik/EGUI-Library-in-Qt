#ifndef BOOKLISTWIDGET_H
#define BOOKLISTWIDGET_H


#include<QTableWidget>
#include<QSortFilterProxyModel>
#include"tablemodel.h"
class BookListWidget : public QTableWidget
{

    Q_OBJECT

public:
    BookListWidget(QWidget *parent = 0);
    void readFromFile();
    void setUp();
    QVector<QString> setComboBox();
public slots:
 //  void showAddEntryDialog();
    void addEntry(QString author,QString title, QString year);
    void editEntry();
    void removeEntry();
    void setTableView(QTableView*& tableview);
    void filterEntry(QString author,QString title, QString year);

signals:
    void selectionChanged(const QItemSelection &selected);
private:


    QTableView *tableView;
    QSortFilterProxyModel *proxyModel;

};

#endif // BOOKLISTWIDGET_H
