#pragma once
#define _USE_MATH_DEFINES
#include <iomanip>
#include <math.h>
#include <string>

using namespace std;

const int MaxStackSize = 100; 

#define USE_SET 

#ifndef USE_SET

template <class T>
struct TNode{
	T val;
	TNode<T> *pNext;
};

template <class T>
class TStack
{
private:
	TNode<T> *pFirst;
public:
	TStack() {
		pFirst = NULL;
	}


	~TStack() {
		TNode<T> *tmp = pFirst;
		while (pFirst != NULL) {
			pFirst = pFirst->pNext;
			delete tmp;
			tmp = pFirst;
		}
	}

	TStack(const TStack<T>& st) {
		TNode<T> *tmp = st.pFirst;
		if (tmp == NULL) {
			pFirst = tmp;
		}
		while (tmp != NULL) {
			Push(tmp->val);
			tmp = tmp->pNext;
		}
		delete tmp;
	}

	TStack<T>& operator=(const TStack<T>& st) {
		if (this != &st) {
			if (!IsEmpty()) {
				Clear();
			}
			else {
				TNode<T> *tmp = st.pFirst;
				if (tmp == NULL) {
					pFirst = tmp;
				}
				while (tmp != NULL) {
					Push(tmp->val);
					tmp = tmp->pNext;
				}
				delete tmp;
			}
		}
		return *this;
	}

	bool  IsEmpty()const {
		return pFirst == NULL;
	}


	bool  IsFull()const {
		TNode<T> *tmp;
		tmp = new TNode<T>;
		if (tmp == NULL) {
			return 1;
		}
		else {
			delete tmp;
			return 0;
		}
	}

	void  Push(const T& a) {
		if (IsFull()) {
			char e[] = "Stack is Full";
			throw e;
		}
		else {
			TNode<T> *tmp;
			tmp = new TNode<T>;
			tmp->pNext = pFirst;
			tmp->val = a;
			pFirst = tmp;
		}
	}

	T  Pop() {
		if (IsEmpty()) {
			char e[] = "Stack is Empty";
			throw e;
		}
		else {
			T res = pFirst->val;
			TNode<T> *tmp;
			tmp = pFirst;
			pFirst = pFirst->pNext;
			delete tmp;
			return res;
		}
	}

	T  Top() {
		if (IsEmpty()) {
			char e[] = "Stack is Empty";
			throw e;
		}
		else {
			return pFirst->val;
		}
	}

	void  Clear() {
		TNode<T> *tmp = pFirst;
		while (pFirst != NULL) {
			pFirst = pFirst->pNext;
			delete tmp;
			tmp = pFirst;
		}

	}


};


#else

template <class T>
class TStack{
	T* arr;
	int size;
	int num;

public:
	TStack(int _size = 100) {
		size = _size;
		num = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw "size";
		arr = new T[size];
	}

	TStack(const TStack& st) {
		size = st.size;
		arr = new T[size];
		for (int i = 0; i < size; i++) {
			arr[i] = st.arr[i];
		}
	}

	~TStack() {
		delete[] arr;
	}

	void Push(const T& val) {
		if (IsFull()) throw 1;
		arr[++num] = val;
	}

	T Pop(void) {
		if (IsEmpty()) throw 2;
		return arr[num--];
	}

	bool IsEmpty() {
		return num == -1;
	}

	bool IsFull() {
		return num == size;
	}
	void Clear() {
		num = -1;
	}
};

#endif

class Calculator {
	string expr, postfix;
	TStack<char> stc;
	TStack<double> stdd;
public:
	Calculator() :stc(), stdd() {}
	void SetExpr(const string& _expr) {
		expr += _expr;
	}
	string GetExpr() {
		return expr;
	}
	bool CheckBrackets() {
		stc.Clear();
		for (int i = 0; i < expr.length(); i++) {
			if (expr[i] == '(') stc.Push('(');
			if (expr[i] == ')') {
				if (stc.IsEmpty()) return false;
				stc.Pop();
			}
		}
		return stc.IsEmpty();
	}
	int Prior(char c) {
		if (c == '(') return 0;
		if (c == '+') return 1;
		if (c == '-') return 1;
		if (c == '/') return 2;
		if (c == '*') return 2;
		if (c == '^') return 3;
	}
	string ToPostfix() {
		string str = "(";
		str += expr;
		str += ")";
		postfix = "";
		stc.Clear();
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '(')
				stc.Push('(');
			if (str[i] == 's') {
				stc.Push('s');
				i = i + 2;
			}
			if (str[i] == 'c') {
				stc.Push('c');
				i = i + 2;
			}
			if (str[i] == 'p') {
				postfix += 'p';
				i++;
			}
			if (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
				postfix += str[i];
			}
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
				char t = stc.Pop();
				postfix += ' ';
				while (Prior(str[i]) <= Prior(t)) {
					postfix += t;
					t = stc.Pop();
				}
				stc.Push(t);
				stc.Push(str[i]);
			}
			if (str[i] == ')') {
				char t = stc.Pop();
				while (t != '(') {
					postfix += ' ';
					postfix += t;
					t = stc.Pop();
				}
				if (!stc.IsEmpty()) t = stc.Pop();
				if (t == 's') {
					postfix += ' ';
					postfix += t;
				}
				else {
					if (t == 'c') {
						postfix += ' ';
						postfix += t;
					}
					else stc.Push(t);
				}
			}

		}
		char y = stc.Pop();
		if (!stc.IsEmpty()) throw 22;
		stdd.Push(y);
		return postfix;
	}
	double Calculate() {
		stdd.Clear();
		for (int i = 0; i < postfix.size(); i++) {
			if (postfix[i] == ' ') continue;
			if (postfix[i] == 'p') stdd.Push(M_PI);
			if (postfix[i] <= '9' && postfix[i] >= '0' || postfix[i] == '.') {
				char *tmp;
				double d = strtod(&postfix[i], &tmp);
				stdd.Push(d);
				i += tmp - &postfix[i] - 1;
			}
			if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
				double op1, op2 = stdd.Pop();
				op1 = stdd.Pop();
				if (postfix[i] == '+') {
					double res = op1 + op2;
					stdd.Push(res);
				}
				if (postfix[i] == '-') {
					double res = op1 - op2;
					stdd.Push(res);
				}
				if (postfix[i] == '*') {
					double res = op1 * op2;
					stdd.Push(res);
				}
				if (postfix[i] == '/') {
					double res = op1 / op2;
					stdd.Push(res);
				}
				if (postfix[i] == '^') {
					double res = pow(op1, op2);
					stdd.Push(res);
				}
			}
			if (postfix[i] == 's' || postfix[i] == 'c') {
				double op = stdd.Pop();
				if (postfix[i] == 's') {
					double res = sin(op);
					stdd.Push(res);
				}
				if (postfix[i] == 'c') {
					double res = cos(op);
					stdd.Push(res);
				}
			}
		}
		double y = stdd.Pop();
		if (!stdd.IsEmpty()) throw 23;
		stdd.Push(y);
		return stdd.Pop();
	}
};


