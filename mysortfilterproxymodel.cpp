#include "mysortfilterproxymodel.h"



MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) :
     QSortFilterProxyModel(parent)
{


   authorRegExp.setCaseSensitivity(Qt::CaseInsensitive);
   titleRegExp.setCaseSensitivity(Qt::CaseInsensitive);
   yearRegExp.setCaseSensitivity(Qt::CaseInsensitive);
   yearRegExp.setPatternSyntax(QRegExp::RegExp);
   titleRegExp.setPatternSyntax(QRegExp::RegExp);
   authorRegExp.setPatternSyntax(QRegExp::RegExp);
}

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

    return (sourceModel()->data(index0).toString().contains(authorRegExp)
            && sourceModel()->data(index1).toString().contains(titleRegExp)
            && sourceModel()->data(index2).toString().contains(yearRegExp));

}
