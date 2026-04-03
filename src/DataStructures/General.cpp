#include <DataStructures/General.hpp>


GeneralData::GeneralData() {
	selected_ds = LINKED_LIST;
	li = LinkedList();
	mp_chain = HashMapChaining(7);
	bst_tree = AVL(0);
	avl_tree = AVL(1);
	tri = Trie();
}

void GeneralData::reset_current() {
	switch (selected_ds) {
	case LINKED_LIST:
		li.clear();
		break;
	case HASHMAP_CHAIN:
		mp_chain.clear();
		break;
	case BST_TREE:
		bst_tree.clear();
		break;
	case AVL_TREE:
		avl_tree.clear();
		break;
	case TRIE:
		tri.clear();
		break;
	}
}

DS GeneralData::get_current_type() {
	return selected_ds;
}

void* GeneralData::get_current_structure() {
	switch (selected_ds) {
	case LINKED_LIST:
		return (void*)&li;
	case HASHMAP_CHAIN:
		return (void*)&mp_chain;
	case BST_TREE:
		return (void*)&bst_tree;
	case AVL_TREE:
		return (void*)&avl_tree;
	case TRIE:
		return (void*)&tri;
	}
	return nullptr;
}

void GeneralData::change_data_structure(DS st) {
	reset_current();
	selected_ds = st;
}

void GeneralData::next_data_structure() {
	change_data_structure((DS)((int)(selected_ds + 1) % 5));
}
void GeneralData::previous_data_structure() {
	change_data_structure((DS)((int)(selected_ds + 4) % 5));
}

void GeneralData::insert(std::string s) {
	switch (selected_ds) {
	case LINKED_LIST:
		li.insert(s);
		break;
	case HASHMAP_CHAIN:
		mp_chain.insert(s);
		break;
	case BST_TREE:
		bst_tree.insert(std::stoi(s));
		break;
	case AVL_TREE:
		avl_tree.insert(std::stoi(s));
		break;
	case TRIE:
		tri.insert(s);
		break;
	}
}
bool GeneralData::erase(std::string s) {
	switch (selected_ds) {
	case LINKED_LIST:
		return li.erase(s);
	case HASHMAP_CHAIN:
		mp_chain.erase(s);
		break;
	case BST_TREE:
		bst_tree.erase(std::stoi(s));
		break;
	case AVL_TREE:
		avl_tree.erase(std::stoi(s));
		break;
	case TRIE:
		tri.erase(s);
		break;
	}
}
void* GeneralData::search(std::string s) {
	switch (selected_ds) {
	case LINKED_LIST:
		return (void*)li.search(s);
	case HASHMAP_CHAIN:		
		return (void*)mp_chain.search(s);
	case BST_TREE:
		return (void*)bst_tree.search(std::stoi(s));
	case AVL_TREE:		
		return (void*)avl_tree.search(std::stoi(s));
	case TRIE:
		return (void*)tri.search(s);
	}
	return nullptr;
}
