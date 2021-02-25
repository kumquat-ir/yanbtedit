#include "nbt_tree_view.h"
#include "libyanbt/nbtread.h"

nbt_tree_view::nbt_tree_view(std::filesystem::path ifpath) : nbt_data(read_nbt(ifpath)) {
	root_tag = &nbt_data.root_tag;
}

nbt_tree_view::~nbt_tree_view(){

}

nbttag* nbt_tree_view::get_item(const QModelIndex &index) const {
	if(index.isValid()){
		nbttag* tag = static_cast<nbttag*>(index.internalPointer());
		if(tag){
			return tag;
		}
	}
	return root_tag;
}

QVariant nbt_tree_view::data(const QModelIndex &index, int role = Qt::DisplayRole) const {
	if(index.isValid()){
		nbttag* tag = get_item(index);
		return QString::fromStdString(tag->payload_str());
	}
	return QVariant();
}

QModelIndex nbt_tree_view::index(int row, int column, const QModelIndex &parent) const {
	if(parent.isValid() && parent.column()!=0){
		return QModelIndex();
	}
	nbttag* parent_tag = get_item(parent);
	if(!parent_tag){
		return QModelIndex();
	}
	nbttag* child_tag = parent_tag->get_child(row);
	if(child_tag){
		return createIndex(row, column, child_tag);
	}
	return QModelIndex();
}

QModelIndex nbt_tree_view::parent(const QModelIndex &index) const {
	if(!index.isValid()){
		return QModelIndex();
	}
	nbttag* child_tag = get_item(index);
	nbttag* parent_tag = child_tag ? child_tag->get_parent() : nullptr;
	if(parent_tag == root_tag || !parent_tag){
		return QModelIndex();
	}
	//fails because the nbtdata is initialized with garbage pointers, due to value-initializing it at the end. needs fix, current implementation is in libyanbt/nbtparse
	return createIndex(parent_tag->get_child_index(child_tag), 0, parent_tag);
}

int nbt_tree_view::rowCount(const QModelIndex &parent) const {
	nbttag* parent_tag = get_item(parent);
	//i think
	return parent_tag ? parent_tag->length : 0;
}

int nbt_tree_view::columnCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	/* name, type, payload */
	return 3;
}
