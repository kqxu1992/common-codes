#include "memorypool.h"
#include <stdio.h>
#include <queue>
#include <stack>
using namespace std;
typedef struct node node;
struct node {
	int value;
	struct node* left;
	struct node* right;
	node(int v):value(v),left(NULL),right(NULL){ } //初始化队列效率更高
};
/*	        1
	    2	     3
	 4    5   6     7

按层序构建二叉树，采用单向队列queue
按层压入，先进先出；

如果按序列中间值为根，则队列为中序遍历的结果，可采用迭代法构建，非迭代法？
*/
node* buildNodeList()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	std::queue<node*> st;
	int n = sizeof(arr) / sizeof(int);
	node* head = new node(arr[0]);
	st.push(head);
	int i = 1;
	while (!st.empty()) {
		node* inode = st.front();
		st.pop();
		for(int k = 0; k < 2 && i < n; k++) {
			node* child = new node(arr[i++]);
			if (k == 0)
				inode->left = child;
			else
				inode->right = child;
			st.push(child);
		}
	}
	return head;
}

/***
****DFS(Deep First Search)深度优先搜索。 BFS(Breath First Search)广度优先搜索
****遍历方式1：深度遍历
****遍历顺序：前序，中序，后序
****算法：递归，栈队列, 非栈非递归
****Morris遍历为非栈非递归遍历，这里没有记录
****
****遍历方式2：层序遍历
****/
void dfs_recursion_before(node* head)
{
	if (!head) return;
	printf("%d ", head->value);
	dfs_recursion_before(head->left);
	dfs_recursion_before(head->right);
}

void dfs_stack_before1(node* head)
{
	printf("dfs_stack_before1:\n");
	if (!head) return;
	std::stack<node*> st;
	st.push(head);
	while (!st.empty()) {
		node* tmp = st.top();
		st.pop();
		printf("%d ", tmp->value);
		if (tmp->right) st.push(tmp->right);
		if (tmp->left) st.push(tmp->left);
	}
	printf("\n");
}

void dfs_stack_before2(node* head)
{
	printf("dfs_stack_before2:\n");
	if (!head) return;
	std::stack<node*> st;

	while (head || !st.empty()) {
		//先访问再压入，中 左
		if (head) {
			printf("%d ", head->value);
			st.push(head);
			head = head->left;
		} // 获取右子节点
		else {
			head = st.top();
			st.pop();
			head = head->right;  //这不直接压入，还没访问
		}
	}
	printf("\n");
}


void dfs_recursion_middle(node* head)
{
	if (!head) return;
	dfs_recursion_middle(head->left);
	printf("%d ", head->value);
	dfs_recursion_middle(head->right);
}

void dfs_stack_middle(node* head)
{
	printf("dfs_stack_middle:\n");
	if (!head) return;
	std::stack<node*> st;

	while (head || !st.empty()) {
		//先压入左边
		if (head) {
			st.push(head);
			head = head->left;
		} //再访问 左中，
		else {
			head = st.top();
			st.pop();
			printf("%d ", head->value);
			head = head->right;
		}
	}
	printf("\n");
}

void dfs_recursion_after(node* head)
{
	if (!head) return;
	dfs_recursion_after(head->left);
	dfs_recursion_after(head->right);
	printf("%d ", head->value);
}

//后面遍历顺序：左 右 中， 法一：采用dfs_stack_before1类似的方法
//dfs_stack_before1 是 中 左 右， 则 dfs_stack_after1 先 右 左 中，再反转 
void dfs_stack_after1(node* head)
{
	printf("dfs_stack_after1:\n");
	if (!head) return;
	std::stack<node*> st;
	st.push(head);
	std::vector<int> arr;
	while (!st.empty()) {
		node* tmp = st.top();
		st.pop();
		arr.push_back(tmp->value);
		if (tmp->left) st.push(tmp->left);
		if (tmp->right) st.push(tmp->right);
	}
	reverse(arr.begin(), arr.end());
	for (int i = 0; i < arr.size(); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/*
后序迭代的最关键的地方就是根节点的访问时机，
由于后序遍历是按照 左-右-中 的顺序，
所以迭代过程中我们应该先处理左子树，返回到根节点，
再处理右子树，再访问根节点。迭代过程会遇到两次根节点，
而第二次才能访问根节点。这里处理方法有很多，比如借助标记结点，
借用辅助栈，更改树的结构等等。不过我觉得最简洁的方法还是借助标记结点。
*/
void dfs_stack_after2(node* head)
{
	printf("dfs_stack_after2:\n");
	if (!head) return;
	std::stack<node*> st;
	node* last_visit_node = NULL;
	while (head || !st.empty()) {
		if (head) {
			st.push(head);
			head = head->left;
		}
		else {
			head = st.top();
			if (!head->right || last_visit_node == head->right) {
				printf("%d ", head->value);
				st.pop();
				last_visit_node = head;
				head = NULL;
			}
			else {
				//st.push(head->right); 错误
				head = head->right;
			}
		}


	}
	printf("\n");
}

void bfs_queue(node* head)
{
	printf("bfs_queue\n");
	std::queue<node*> que;
	que.push(head);
	while (!que.empty()) {
		head = que.front();
		que.pop();
		printf("%d ", head->value);
		if (head->left) que.push(head->left);
		if (head->right) que.push(head->right);
	}
	printf("\n");
}
int main(int argc, char* argv[])
{
	node* head = buildNodeList();
	printf("rescursion before\n");
	dfs_recursion_before(head);
	printf("\nrescursion middle\n");
	dfs_recursion_middle(head);
	printf("\nrescursion after\n");
	dfs_recursion_after(head);
	printf("\n");
	dfs_stack_before1(head);

	dfs_stack_before2(head);

	dfs_stack_middle(head);

	dfs_stack_after1(head);

	dfs_stack_after2(head);

	bfs_queue(head);
	system("pause");
	return 0;
	
}