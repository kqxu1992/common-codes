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
	node(int v):value(v),left(NULL),right(NULL){ } //��ʼ������Ч�ʸ���
};
/*	        1
	    2	     3
	 4    5   6     7

�����򹹽������������õ������queue
����ѹ�룬�Ƚ��ȳ���

����������м�ֵΪ���������Ϊ��������Ľ�����ɲ��õ������������ǵ�������
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
****DFS(Deep First Search)������������� BFS(Breath First Search)�����������
****������ʽ1����ȱ���
****����˳��ǰ�����򣬺���
****�㷨���ݹ飬ջ����, ��ջ�ǵݹ�
****Morris����Ϊ��ջ�ǵݹ����������û�м�¼
****
****������ʽ2���������
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
		//�ȷ�����ѹ�룬�� ��
		if (head) {
			printf("%d ", head->value);
			st.push(head);
			head = head->left;
		} // ��ȡ���ӽڵ�
		else {
			head = st.top();
			st.pop();
			head = head->right;  //�ⲻֱ��ѹ�룬��û����
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
		//��ѹ�����
		if (head) {
			st.push(head);
			head = head->left;
		} //�ٷ��� ���У�
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

//�������˳���� �� �У� ��һ������dfs_stack_before1���Ƶķ���
//dfs_stack_before1 �� �� �� �ң� �� dfs_stack_after1 �� �� �� �У��ٷ�ת 
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
�����������ؼ��ĵط����Ǹ��ڵ�ķ���ʱ����
���ں�������ǰ��� ��-��-�� ��˳��
���Ե�������������Ӧ���ȴ��������������ص����ڵ㣬
�ٴ������������ٷ��ʸ��ڵ㡣�������̻��������θ��ڵ㣬
���ڶ��β��ܷ��ʸ��ڵ㡣���ﴦ�����кܶ࣬���������ǽ�㣬
���ø���ջ���������Ľṹ�ȵȡ������Ҿ�������ķ������ǽ�����ǽ�㡣
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
				//st.push(head->right); ����
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