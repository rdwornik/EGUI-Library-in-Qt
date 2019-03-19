#include "tablemodel.h"
#include <QString>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel (parent)
{

}

TableModel::TableModel(QList<Book> book, QObject *parent)
    : QAbstractTableModel (parent),
      books(book)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return books.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
        return 3;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        if (index.row() >= books.size() || index.row() < 0)
            return QVariant();

        if (role == Qt::DisplayRole) {
            const auto &book = books.at(index.row());

            if (index.column() == 0)
                return book.author;
            else if (index.column() == 1)
                return book.title;
            else if (index.column() == 2)
                return book.year;
        }
        return QVariant();
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return tr("Author");

                case 1:
                    return tr("Title");

                case 2:
                    return tr("Year");

                default:
                    return QVariant();
            }
        }
        return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return Qt::ItemIsEnabled;

        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
            int row = index.row();

            auto book = books.value(row);

            if (index.column() == 0)
                book.author = value.toString();
            else if (index.column() == 1)
                book.title = value.toString();
            else if (index.column() == 2)
                book.year = value.toString();
            else
                return false;

            books.replace(row, book);
            emit dataChanged(index, index, {role});

            return true;
        }

        return false;
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);

        beginInsertRows(QModelIndex(), position, position + rows - 1);

        for (int row = 0; row < rows; ++row)
            books.insert(position,{QString(), QString(),QString()});

        endInsertRows();
        return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
        beginRemoveRows(QModelIndex(), position, position + rows - 1);

        for (int row = 0; row < rows; ++row)
            books.removeAt(position);

        endRemoveRows();
        return true;
}

QList<Book> TableModel::getBooks() const
{
    return books;
}
