#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct node {
	int data;
	struct node* pLeft;
	struct node* pRight;
};
typedef struct node NODE;
typedef NODE* TREE;

void KhoiTaoCay(TREE& t) {
	t = NULL;
}

void ThemNodeVaoCay(TREE& t, int x) {
	if (t == NULL) {
		NODE* p = new NODE;
		p->data = x;
		p->pLeft = NULL;
		p->pRight = NULL;
		t = p;
	}
	else {
		if (t->data > x) {
			ThemNodeVaoCay(t->pLeft, x);
		}
		else if (t->data < x) {
			ThemNodeVaoCay(t->pRight, x);
		}
	}
}

void NLR_traversal(TREE t) {
	if (t != NULL) {
		cout << t->data << " ";
		NLR_traversal(t->pLeft);
		NLR_traversal(t->pRight);
	}
}
void NRL_traversal(TREE t) {
	if (t != NULL) {
		cout << t->data << " ";
		NRL_traversal(t->pRight);
		NRL_traversal(t->pLeft);
	}
}

void LNR_traversal(TREE t) {
	if (t != NULL) {
		LNR_traversal(t->pLeft);
		cout << t->data << " ";
		LNR_traversal(t->pRight);
	}
}//Duyet cac phan tu tu be den lon
void RNL_traversal(TREE t) {
	if (t != NULL) {
		RNL_traversal(t->pRight);
		cout << t->data << " ";
		RNL_traversal(t->pLeft);
	}
}//Duyet cac phan tu tu be den lon

void LRN_traversal(TREE t) {
	if (t != NULL) {
		LRN_traversal(t->pLeft);
		LRN_traversal(t->pRight);
		cout << t->data << " ";
	}
}
void RLN_traversal(TREE t) {
	if (t != NULL) {
		RLN_traversal(t->pRight);
		RLN_traversal(t->pLeft);
		cout << t->data << " ";
	}
}

void Menu(TREE t) {
	cout << "\n\n\t\t =============MENU============";
	cout << "\n1. Nhap du lieu";
	cout << "\n2. Xuat du lieu cay theo NLR";
	cout << "\n0. Ket thuc";
	cout << "\n\n\t\t =============================";
	cout << "\n";
	while (true) {
		int opt;
		cout << "Nhap lua chon: ";
		cin >> opt;

		if (opt < 0 || opt > 2) {
			cout << "Lua chon khong hop le";
		}
		else if (opt == 1) {
			int x;
			cout << "Nhap so nguyen: ";
			cin >> x;
			ThemNodeVaoCay(t, x);
		}
		else if (opt == 2) {
			cout << "\t\t Duyet Cay Theo NLR: ";
			NLR_traversal(t);
			cout << "\n";
		}
		else break;
	}
}

void Iterative_Preorder_Traversal2(TREE t) {
	stack <TREE> st;
	while (t != NULL) {
		cout << t->data << " ";
		st.push(t);
		t = t->pLeft;
	}
	while (!st.empty()) {
		TREE* temp = &st.top()->pRight;
		while (*temp != NULL) {
			if ((*temp)->pLeft != NULL) {
				Iterative_Preorder_Traversal2(*temp);
			}
			else {
				cout << (*temp)->data << " ";
			}
			*temp = (*temp)->pRight;
		}
		st.pop();
	}
}


void Iterative_Preorder_Traversal(TREE t) {
	stack <TREE> st;
	while (t != NULL || !st.empty()) {
		if (t != NULL) {
			cout << t->data << " ";
			st.push(t);
			t = t->pLeft;
		}
		else {
			t = st.top();
			st.pop();
			t = t->pRight;
		}
	}
}
vector<int> Iterative_preorderTraversal(TREE root) {
	vector<int> res;
	if (root == nullptr) {
		return res;
	}

	stack<TREE> s;
	s.push(root);
	while (!s.empty()) {
		TREE tmp = s.top();
		s.pop();
		res.push_back(tmp->data);
		// pay more attention to this sequence
		if (tmp->pRight != nullptr) {
			s.push(tmp->pRight);
		}
		if (tmp->pLeft != nullptr) {
			s.push(tmp->pLeft);
		}
	}
	return res;
}

void Nonrecursive_Inorder_Traversal(TREE t) {
	stack<TREE> st;
	while (t != NULL || !st.empty()) {
		if (t != NULL) {
			st.push(t);
			t = t->pLeft;
		}
		else {
			cout << st.top()->data << " ";
			if (st.top()->pRight != NULL) {
				t = st.top()->pRight;
			}
			st.pop();

		}
	}
}
vector<int> inorderTraversal(TREE root) {
	vector<int> res;
	stack<TREE> s;

	TREE currentNode = root;
	bool done = false;
	while (!done) {
		if (currentNode != nullptr) {
			s.push(currentNode);
			currentNode = (currentNode)->pLeft;
		}
		else {
			if (s.empty()) {
				done = true;
			}
			else {
				currentNode = s.top();
				s.pop();
			}
			if (currentNode != NULL) {
				res.push_back(currentNode->data);
				currentNode = currentNode->pRight;
			}
		}
	}

	return res;
}


vector <int> Nonrecursive_LRN(TREE t) {
	vector<int> res;
	if (t == nullptr) {
		return res;
	}

	stack<TREE> st;
	st.push(t);
	TREE prev = nullptr;
	while (!st.empty()) {
		TREE curr = st.top();
		// prev là cha của curr
		if (prev == nullptr || prev->pLeft == curr || prev->pRight == curr) {
			//prev == nullptr điều kiện khởi đầu 
			
			//prev->pLeft == curr || prev->pRight == curr là điều kiện dùng để xét
			//khi prev đi tới nút lá. Khi đó, curr sẽ quay lên trên và prev là nút lá
			if (curr->pLeft != nullptr) {
				st.push(curr->pLeft);
				//duyệt hết phần cây bên trái cùng
			}
			else if (curr->pRight == nullptr || curr->pRight == prev) {
				//curr->pRight == nullptr : Khi curr là nút lá
				//curr->pRight == prev: Khi prev đóng vai trò là nút lá, curr quay lên trên.
				res.push_back(curr->data);
				st.pop();
			}
			else {
				st.push(curr->pRight);
				//Trường hợp tồn tại cây con nhận curr->pRight làm root
			}
		}
		else if (curr->pLeft == prev) {
			//Trường hợp curr từ node lá quay lên lần đầu
			//Khi đó, prev vẫn là node lá
			if (curr->pRight != nullptr) {
				st.push(curr->pRight);
				//Trường hợp tồn tại cây con nhận node prev là root và chỉ có right child
			}
			else {
				res.push_back(curr->data);
				st.pop();
			}
		}
		else {
			res.push_back(curr->data);
			st.pop();
			//Khi đã duyệt hết node trái phải thì visit node cha
		}
		prev = curr;
		//Chỉnh lại thứ tự cho prev
	}

	return res;
}

vector<vector<int>> level_traversal(TREE t) {
	int lv = 0;
	queue<TREE> q;
	q.push(t);
	q.push(nullptr);
	vector<vector<int>> res;
	if (t == nullptr) {
		return res;
	}
	vector<int> curr;
	while (!q.empty()) {
		TREE temp = q.front();
		q.pop();
		if (temp != nullptr) {
			curr.push_back(temp->data);
			if (temp->pLeft != nullptr) {
				q.push(temp->pLeft);
			}
			if (temp->pRight != nullptr) {
				q.push(temp->pRight);
			}
		}
		else {
			vector<int> c_curr(curr);
			res.push_back(c_curr);
			curr.clear(); // C++ không tự động giải phóng bộ nhớ, cần phải xóa tay
			if (!q.empty()) {
				q.push(nullptr);
			}
		}
	}

	return res;
}
int main() {
	TREE t;
	KhoiTaoCay(t);
	int n; cin >> n;
	
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		ThemNodeVaoCay(t, x);
	}
	
	cout << "Duyet theo LRN: ";
	LRN_traversal(t);
	cout << endl;

	cout << "Nonrecursive LRN: ";
	for (int& x : Nonrecursive_LRN(t)) cout << x << " ";
	cout << endl;

	cout << "Level traversal: " << endl;
	vector<vector<int>> res = level_traversal(t);
	for (int i = 0; i < res.size(); i++) {
		for (int& x : res[i]) cout << x << " ";
		cout << endl;
	}
	return 0;
}