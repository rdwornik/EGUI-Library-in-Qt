#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public: 
    MySortFilterProxyModel(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
public slots:
    void setAuthorFilter(const QString& regExp){
        authorRegExp.setPattern(regExp);
        invalidateFilter();
    }
    void setTitleFilter(const QString& regExp){
        titleRegExp.setPattern(regExp);
        invalidateFilter();
    }
    void setYearFilter(const QString& regExp){
        yearRegExp.setPattern(regExp);
        invalidateFilter();
    }

    void setFilter(QString author, QString title, QString year){
        authorRegExp.setPattern(author);
        titleRegExp.setPattern(title);
        yearRegExp.setPattern(year);
        invalidateFilter();
    }
private:
    QRegExp authorRegExp;
    QRegExp titleRegExp;
    QRegExp yearRegExp;

};

#endif // MYSORTFILTERPROXYMODEL_H
