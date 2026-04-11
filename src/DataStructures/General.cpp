#include <DataStructures/General.hpp>
#include <iostream>

GeneralData::GeneralData() {
	selected_ds = LINKED_LIST;
	li = LinkedList();
	mp_chain = HashMapChaining(7);
	avl_tree = AVL(1);
	tri = Trie();
	dijkstra = Dijkstra();
	kruskal = Kruskal();
}

std::string get_ds_name(DS name) {
	switch (name) {
	case LINKED_LIST:
		return "Linked List";
	case HASHMAP_CHAIN:
		return "Hash Table";
	case AVL_TREE:
		return "AVL Tree";
	case TRIE:
		return "Trie";
	case KRUSKAL:
		return "Kruskal algorithm";
	case DIJKSTRA:
		return "Dijkstra algorithm";
	default:
		return "";
	}
}


void GeneralData::reset_current() {
	switch (selected_ds) {
	case LINKED_LIST:
		li.clear();
		break;
	case HASHMAP_CHAIN:
		mp_chain.clear();
		break;
	case AVL_TREE:
		avl_tree.clear();
		break;
	case TRIE:
		tri.clear();
		break;
	case KRUSKAL:
		kruskal.clear();
		break;
	case DIJKSTRA:
		dijkstra.clear();
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
	case AVL_TREE:
		return (void*)&avl_tree;
	case TRIE:
		return (void*)&tri;
	case KRUSKAL:
		return (void*)&kruskal;
	case DIJKSTRA:
		return (void*)&dijkstra;
	}
	return nullptr;
}

void GeneralData::change_data_structure(DS st) {
	reset_current();
	selected_ds = st;
}

void GeneralData::next_data_structure() {
	change_data_structure((DS)((int)(selected_ds + 1) % TOTAL_DS_COUNT));
}
void GeneralData::previous_data_structure() {
	change_data_structure((DS)((int)(selected_ds + TOTAL_DS_COUNT - 1) % TOTAL_DS_COUNT));
}

bool GeneralData::insert(std::string s) {
	
	switch (selected_ds) {
		case LINKED_LIST:
			li.insert(s);
			return true;
		case HASHMAP_CHAIN:
			mp_chain.insert(s);
			return true;
		case AVL_TREE:
			avl_tree.insert(std::stoi(s));
			return true;
		case TRIE:
			tri.insert(s);
			return true;
		case KRUSKAL:
		{
			std::vector<int> arr;
			for (char c : s) {
				if (c == ' ') arr.push_back(0);
				else arr.back() = arr.back() * 10 + (c - '0');
			}
			if (arr.size() != 3) assert(false);
			kruskal.add_edge(arr[0], arr[1], arr[2]);
			return true;
		}
		case DIJKSTRA:
		{
			std::vector<int> arr;
			for (char c : s) {
				if (c == ' ') arr.push_back(0);
				else arr.back() = arr.back() * 10 + (c - '0');
			}
			if (arr.size() != 3) assert(false);
			std::cout << arr[0] << " " << arr[1] << " " << arr[2] << "\n";
			dijkstra.add_edge(arr[0], arr[1], arr[2]);
			return true;
		}
	}
	return false;
}
bool GeneralData::erase(std::string s) {
	switch (selected_ds) {
	case LINKED_LIST:
		return li.erase(s);
	case HASHMAP_CHAIN:
		return mp_chain.erase(s);
	case AVL_TREE:
		return avl_tree.erase(std::stoi(s));
	case TRIE:
		return tri.erase(s);
	case KRUSKAL:
		{
			std::vector<int> arr;
			for (char c : s) {
				if (c == ' ') arr.push_back(0);
				else arr.back() = arr.back() * 10 + (c - '0');
			}
			if (arr.size() != 3) assert(false);
			return kruskal.del_edge(arr[0], arr[1], arr[2]);
		}
	case DIJKSTRA:
		{
			std::vector<int> arr;
			for (char c : s) {
				if (c == ' ') arr.push_back(0);
				else arr.back() = arr.back() * 10 + (c - '0');
			}
			if (arr.size() != 3) assert(false);
			return dijkstra.del_edge(arr[0], arr[1], arr[2]);
		}
	}
	return false;
}
std::vector<void*> GeneralData::search(std::string s) {
	switch (selected_ds) {
	case LINKED_LIST:
		return li.search(s);
	case HASHMAP_CHAIN:		
		return mp_chain.search(s);
	case AVL_TREE:		
		return avl_tree.search(std::stoi(s));
	case TRIE:
		return tri.search(s);
	}

	std::vector<void*> empty;
	return empty;
}

void GeneralData::run() {
	
}

bool GeneralData::is_drawing_ds() {
	return (int)selected_ds <= 3;
}