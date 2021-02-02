#ifndef NBT_TREE_VIEW_H
#define NBT_TREE_VIEW_H

#include <QAbstractItemModel>
#include <filesystem>
#include "libyanbt/nbtfile.h"

class nbt_tree_view : public QAbstractItemModel {
	Q_OBJECT
public:
	nbtfile nbt_data;
	nbttag* root_tag;
	nbttag* get_item(const QModelIndex&) const;

	nbt_tree_view(std::filesystem::path);
	~nbt_tree_view();

	QVariant data(const QModelIndex &index, int role) const override;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
};

#endif // NBT_TREE_VIEW_H
