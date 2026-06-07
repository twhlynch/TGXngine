#pragma once

#include <iostream>
#include <sstream>
#include <type_traits>
#include "Core.h"

namespace WoS
{
template <typename Enumeration>
auto as_integer(Enumeration const value)
	-> std::underlying_type_t<Enumeration>
{
	return static_cast<std::underlying_type_t<Enumeration>>(value);
}

enum class TreeColor : std::uint8_t
{
	Black = 0,
	Red = 1
};

template <typename T>
struct TreeNode
{
	T data;
	TreeNode *parent;
	TreeNode *left;
	TreeNode *right;
	TreeColor color; // 1 -> Red, 0 -> Black
};

template <typename T>
class Tree
{
private:
	TreeNode<T> *treeRoot;
	TreeNode<T> *treeNull;
	size_t n;

public:
	Tree()
	{
		treeNull = new TreeNode<T>();
		treeNull->color = TreeColor::Black;
		treeNull->left = treeNull;
		treeNull->right = treeNull;
		treeNull->parent = nullptr;

		treeRoot = treeNull;
		n = 0;
	}

	~Tree()
	{
		PostOrderDeleter(this->treeRoot);
		delete treeNull;
	}

	void Preorder()
	{
		PreOrderHelper(this->treeRoot, std::cout);
	}

	void Inorder()
	{
		InOrderHelper(this->treeRoot, std::cout);
	}

	void Postorder()
	{
		PostOrderHelper(this->treeRoot, std::cout);
	}

	TreeNode<T> *Search(T node)
	{
		return SearchTreeHelper(this->treeRoot, node);
	}

	void Insert(T key)
	{
		TreeNode<T> *parent = nullptr;
		TreeNode<T> *current = this->treeRoot;

		while (current != treeNull)
		{
			parent = current;

			if (key < current->data)
			{
				current = current->left;
			}
			else if (key > current->data)
			{
				current = current->right;
			}
			else
			{
				// duplicate key
				return;
			}
		}

		auto *node = new TreeNode<T>();
		node->data = key;
		node->parent = parent;
		node->left = treeNull;
		node->right = treeNull;
		node->color = TreeColor::Red;

		if (parent == nullptr)
		{
			this->treeRoot = node;
		}
		else if (key < parent->data)
		{
			parent->left = node;
		}
		else
		{
			parent->right = node;
		}

		if (node->parent == nullptr)
		{
			node->color = TreeColor::Black;
			n++;
			return;
		}

		if (node->parent->parent == nullptr)
		{
			n++;
			return;
		}

		n++;
		InsertIntoTree(node);
	}

	bool Contains(T key)
	{
		TreeNode<T> *node = this->treeRoot;

		while (node != treeNull)
		{
			if (node->data == key)
			{
				return true;
			}

			if (key < node->data)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}

		return false;
	}

	void Remove(T key)
	{
		TreeNode<T> *node = this->treeRoot;
		TreeNode<T> *z = treeNull;

		while (node != treeNull)
		{
			if (node->data == key)
			{
				z = node;
				break;
			}
			if (key < node->data)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}

		if (z == treeNull)
		{
			return;
		}

		TreeNode<T> *y = z;
		TreeNode<T> *x = treeNull;
		TreeColor original_color = y->color;

		if (z->left == treeNull)
		{
			x = z->right;
			Transplant(z, z->right);
		}
		else if (z->right == treeNull)
		{
			x = z->left;
			Transplant(z, z->left);
		}
		else
		{
			y = Minimum(z->right);

			original_color = y->color;

			x = y->right;

			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				Transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			Transplant(z, y);

			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		delete z;
		n--;

		if (original_color == TreeColor::Black)
		{
			DeleteFromTree(x);
		}

		if (this->treeRoot != treeNull)
		{
			this->treeRoot->color = TreeColor::Black;
		}
	}

	void Display()
	{
		if (this->treeRoot)
		{
			PrintHelper(this->treeRoot, "", true, std::cout);
		}
	}

	String ToString()
	{
		std::stringstream ss;

		if (this->treeRoot)
		{
			PrintHelper(this->treeRoot, "", true, ss);
		}

		return ss.str();
	}

	String ToStringInorder()
	{
		std::stringstream ss;

		InOrderHelper(this->treeRoot, ss);

		return ss.str();
	}

	String ToStringPreorder()
	{
		std::stringstream ss;

		PreOrderHelper(this->treeRoot, ss);

		return ss.str();
	}

	String ToStringPostorder()
	{
		std::stringstream ss;

		PostOrderHelper(this->treeRoot, ss);

		return ss.str();
	}

	int Size()
	{
		return static_cast<int>(n);
	}

private:
	void InitializeNULLNode(TreeNode<T> *node, TreeNode<T> *parent)
	{
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = TreeColor::Black;
	}

	TreeNode<T> *SearchTreeHelper(TreeNode<T> *node, T key)
	{
		if (node == treeNull || key == node->data)
		{
			return node;
		}

		if (key < node->data)
		{
			return SearchTreeHelper(node->left, key);
		}

		return SearchTreeHelper(node->right, key);
	}

	void InsertIntoTree(TreeNode<T> *k)
	{
		TreeNode<T> *u;

		while (k->parent->color == TreeColor::Red)
		{
			if (k->parent == k->parent->parent->right)
			{
				u = k->parent->parent->left;

				if (u->color == TreeColor::Red)
				{
					u->color = TreeColor::Black;
					k->parent->color = TreeColor::Black;
					k->parent->parent->color = TreeColor::Red;
					k = k->parent->parent;
				}
				else
				{
					if (k == k->parent->left)
					{
						k = k->parent;
						RightRotate(k);
					}

					k->parent->color = TreeColor::Black;
					k->parent->parent->color = TreeColor::Red;
					LeftRotate(k->parent->parent);
				}
			}
			else
			{
				u = k->parent->parent->right;

				if (u->color == TreeColor::Red)
				{
					u->color = TreeColor::Black;
					k->parent->color = TreeColor::Black;
					k->parent->parent->color = TreeColor::Red;
					k = k->parent->parent;
				}
				else
				{
					if (k == k->parent->right)
					{
						k = k->parent;
						LeftRotate(k);
					}

					k->parent->color = TreeColor::Black;
					k->parent->parent->color = TreeColor::Red;
					RightRotate(k->parent->parent);
				}
			}

			if (k == this->treeRoot)
			{
				break;
			}
		}

		this->treeRoot->color = TreeColor::Black;
	}

	void DeleteFromTree(TreeNode<T> *delete_node)
	{
		if (delete_node == treeNull)
		{
			return;
		}
		if (delete_node->parent == nullptr)
		{
			return;
		}

		while (delete_node != this->treeRoot && delete_node->color == TreeColor::Black)
		{
			TreeNode<T> *current;

			if (delete_node == delete_node->parent->left)
			{
				current = delete_node->parent->right;

				if (current->color == TreeColor::Red)
				{
					current->color = TreeColor::Black;
					delete_node->parent->color = TreeColor::Red;
					LeftRotate(delete_node->parent);
					current = delete_node->parent->right;
				}

				if (current->left->color == TreeColor::Black && current->right->color == TreeColor::Black)
				{
					current->color = TreeColor::Red;
					delete_node = delete_node->parent;
				}
				else
				{
					if (current->right->color == TreeColor::Black)
					{
						current->left->color = TreeColor::Black;
						current->color = TreeColor::Red;

						RightRotate(current);

						current = delete_node->parent->right;
					}

					current->color = delete_node->parent->color;
					delete_node->parent->color = TreeColor::Black;
					current->right->color = TreeColor::Black;

					LeftRotate(delete_node->parent);

					delete_node = this->treeRoot;
				}
			}
			else
			{
				current = delete_node->parent->left;

				if (current->color == TreeColor::Red)
				{
					current->color = TreeColor::Black;
					delete_node->parent->color = TreeColor::Red;

					RightRotate(delete_node->parent);

					current = delete_node->parent->left;
				}

				if (current->left->color == TreeColor::Black && current->right->color == TreeColor::Black)
				{
					current->color = TreeColor::Red;
					delete_node = delete_node->parent;
				}
				else
				{
					if (current->left->color == TreeColor::Black)
					{
						current->right->color = TreeColor::Black;
						current->color = TreeColor::Red;

						LeftRotate(current);

						current = delete_node->parent->left;
					}

					current->color = delete_node->parent->color;
					delete_node->parent->color = TreeColor::Black;
					current->left->color = TreeColor::Black;

					RightRotate(delete_node->parent);

					delete_node = this->treeRoot;
				}
			}
		}

		delete_node->color = TreeColor::Black;
	}

	void Transplant(TreeNode<T> *u, TreeNode<T> *v)
	{
		if (u->parent == nullptr)
		{
			this->treeRoot = v;
		}
		else if (u == u->parent->left)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}

		v->parent = u->parent;
	}

	void LeftRotate(TreeNode<T> *x)
	{
		TreeNode<T> *y = x->right;
		x->right = y->left;

		if (y->left != treeNull)
		{
			y->left->parent = x;
		}

		y->parent = x->parent;

		if (x->parent == nullptr)
		{
			this->treeRoot = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}

		y->left = x;
		x->parent = y;
	}

	void RightRotate(TreeNode<T> *x)
	{
		TreeNode<T> *y = x->left;
		x->left = y->right;

		if (y->right != treeNull)
		{
			y->right->parent = x;
		}

		y->parent = x->parent;

		if (x->parent == nullptr)
		{
			this->treeRoot = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}

		y->right = x;
		x->parent = y;
	}

	TreeNode<T> *Minimum(TreeNode<T> *node)
	{
		while (node->left != treeNull)
		{
			node = node->left;
		}

		return node;
	}

	void PreOrderHelper(TreeNode<T> *node, std::ostream &os)
	{
		if (node != treeNull)
		{
			os << '{' << node->data << '}' << " ";
			PreOrderHelper(node->left, os);
			PreOrderHelper(node->right, os);
		}
	}

	void InOrderHelper(TreeNode<T> *node, std::ostream &os)
	{
		if (node != treeNull)
		{
			InOrderHelper(node->left, os);
			os << '{' << node->data << '}' << " ";
			InOrderHelper(node->right, os);
		}
	}

	void PostOrderHelper(TreeNode<T> *node, std::ostream &os)
	{
		if (node != treeNull)
		{
			PostOrderHelper(node->left, os);
			PostOrderHelper(node->right, os);
			os << '{' << node->data << '}' << " ";
		}
	}

	void PostOrderDeleter(TreeNode<T> *node)
	{
		if (node != treeNull)
		{
			PostOrderDeleter(node->left);
			PostOrderDeleter(node->right);
			delete node;
		}
	}

	void PrintHelper(TreeNode<T> *root, String indent, bool last, std::ostream &os)
	{
		// prints the tree on the structure screen
		if (root != treeNull)
		{
			os << indent;

			if (last)
			{
				os << "R----";
				indent += "     ";
			}
			else
			{
				os << "L----";
				indent += "|    ";
			}

			String node_colour = root->color == TreeColor::Red ? "Red" : "Black";
			os << root->data << "(" << node_colour << ")" << "\n";
			PrintHelper(root->left, indent, false, os);
			PrintHelper(root->right, indent, true, os);
		}
	}
};
} // namespace WoS
