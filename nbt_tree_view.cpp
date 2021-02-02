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

QVariant nbt_tree_view::data(const QModelIndex &index, int role) const {

}

QModelIndex nbt_tree_view::index(int row, int column, const QModelIndex &parent) const {

}

QModelIndex nbt_tree_view::parent(const QModelIndex &index) const {

}

int nbt_tree_view::rowCount(const QModelIndex &parent) const {
	nbttag* parent_tag = get_item(parent);
	return parent_tag ? parent_tag->length_recurse() : 0;
}

int nbt_tree_view::columnCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	/* name, type, payload */
	return 3;
}
