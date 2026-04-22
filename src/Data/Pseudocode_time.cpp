#include <Data/Pseudocode_time.hpp>
#include <Helper.hpp>

std::vector<int> get_highlighted_line(int DS_name, int command_name, int stage) { 
	// time since the last stage
	if (DS_name == 1) {
		if (command_name == 1) {
			std::vector<std::vector<int>> ans = { {3}, {3}, {3, 4, 5} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 2) {
			std::vector<std::vector<int>> ans = { {4,5}, {4,5}, {4,5}, {5}, {5}, {5}, { 7 }, {6}, {6} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 3) {
			std::vector<std::vector<int>> ans = { {6,4}, {6,4}, {6,4}, {4,5}, {4,5}, {4,5} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 4) {
			std::vector<std::vector<int>> ans = { {7,4}, {7,4}, {7,4}, {4}, {4}, {4}, {5,6}, {5,6}, {5,6} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
	}
	else if (DS_name == 2) {
		if (command_name == 1) {
			std::vector<std::vector<int>> ans = { {4}, {4}, {4, 5, 6} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 2) {
			std::vector<std::vector<int>> ans = { {10,6}, {10,6}, {10,6}, {6}, {6}, {6}, {8}, {7}, {7} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 3) {
			std::vector<std::vector<int>> ans = { {7,5}, {7,5}, {7,5}, {5,6}, {5,6}, {5,6} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
	}
	else if (DS_name == 3) {
		if (command_name == 1) {
			std::vector<std::vector<int>> ans = { {5,6}, {5,6}, {5,6}, {7,8}, {7,8}, {7,8},
				{}, {2}, {2}, {2,3,4}, {2,3,4}, {2,3,4}, {9}, {9}, {9}, {9,10}, {9,10}, {9,10} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 2) {
			std::vector<std::vector<int>> ans = { {3,4}, {3,4}, {3,4}, {5,6}, {5,6}, {5,6},
				{2}, {2}, {2}, { 8 }, { 8 }, { 8 }, 
				{ 18 }, { 18 }, { 18 }, { 18,19 }, { 18,19 }, { 18,19 },
				{9,10,11,12}, {9,10,11,12}, {9,10,11,12},
				{13,14,15,16}, {13,14,15,16}, {13,14,15,16}
		};
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 3) {
			std::vector<std::vector<int>> ans = { {6,7}, {6,7}, {6,7}, {8,9}, {8,9}, {8,9},
				{2, 3}, {2,3}, {2, 3}, {4, 5}, {4, 5}, {4, 5} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}

	}
	else if (DS_name == 4) {
		if (command_name == 1) {
			std::vector<std::vector<int>> ans = {
				{7}, {7}, {7},
				{5,6}, {5,6}, {5,6},
				{8}, {8}, {8}
			};
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 2) {
			std::vector<std::vector<int>> ans = {
				{6,7},{6,7},{6,7},
				{8,9},{8,9},{8,9},
				{11}, {11}, {11},
				{12,13}, {12,13}, {12,13},
				{16}, {16}, {16},
				{16,17}, {16,17}, {16,17},
				{18,19,20,21},{18,19,20,21},{18,19,20,21}
			};
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 3) {
			std::vector<std::vector<int>> ans = { 
				{6,7}, {6,7}, {6,7}, 
				{4,5}, {4,5}, {4,5},
				{8}, {8}, {8}
			};
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}

	}
	else if (DS_name == 5) {
		if (command_name == 1) {
			std::vector<std::vector<int>> ans = { {2}, {2}, {2} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 2) {
			std::vector<std::vector<int>> ans = { {2}, {2}, {2} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else {
			std::vector<std::vector<int>> ans = { {7,8}, {7,8}, {7,8}, {9}, {9}, {9}, {10,11,12}, {10,11,12} , {10,11,12} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}

	}
	else if (DS_name == 6) {
		if (command_name == 1) {
			std::vector<std::vector<int>> ans = { {2}, {2}, {2} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else if (command_name == 2) {
			std::vector<std::vector<int>> ans = { {2}, {2}, {2} };
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		else {
			std::vector<std::vector<int>> ans = { 
				{9}, {9}, {9},
				{10, 11},{10, 11},{10, 11},
				{13,14,15},{13,14,15},{13,14,15}
			};
			if (1 <= stage && stage <= ans.size())
				return ans[stage - 1];
		}
		
	}
	return {};
}

int f(int prestage, int step){ return prestage * 3 + step - 3; }