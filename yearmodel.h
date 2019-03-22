#ifndef YEARMODEL_H
#define YEARMODEL_H

#include <QAbstractItemModel>
#include <QSet>
#include <QtAlgorithms>
#include <algorithm>
#include <iterator>
#include <set>
class yearModel : public QAbstractListModel
{
public:

    yearModel(QAbstractItemModel &baseModel, QObject *parent = nullptr)
        : QAbstractListModel(parent),base(baseModel){
        updateModel();
        connect(&baseModel, &QAbstractItemModel::dataChanged, this, &yearModel::updateModel);
        connect(&baseModel, &QAbstractItemModel::rowsInserted, this, &yearModel::updateModel);
        connect(&baseModel, &QAbstractItemModel::rowsRemoved, this, &yearModel::updateModel);

    };

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = {}) const{
        return parent.isValid() ? 0 : items.size();
    };
    QVariant data(const QModelIndex &index, int role) const{
        if(role != Qt::DisplayRole) return {};
        return items.at(index.row());
    };

    void updateModel(){
        beginResetModel();
        items.clear();
        QSet<int> set;
        int year;
        for (int i = 0; i < base.rowCount(); i++){
         if((year = base.index(i,2).data().toInt()))
                set.insert(year);
        }

        std::transform(set.begin(),set.end(),std::back_inserter(items),[=](int i) -> QString{
            return QString::number(i);
        });
        std::sort(items.begin(),items.end(),std::greater<QString>());

        endResetModel();

    }
private:
    QStringList items;
    QAbstractItemModel &base;
};

#endif // YEARMODEL_H
