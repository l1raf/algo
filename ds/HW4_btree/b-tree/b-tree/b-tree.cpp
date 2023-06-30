#include <iostream>
#include <fstream>

using namespace std;

class BNode
{
public:
	BNode(int, bool);
	~BNode();
	pair<int, int>* keys; // key-value pairs
	int t; // minimum degree
	bool leaf;
	BNode** children;
	unsigned int size; // number of keys
};

class BTree
{
private:
	BNode* root;
	int t;
	void nodeInsert(BNode*, pair<int, int>);
	pair<bool, int> recursiveSearch(int, BNode*);
	void splitChild(BNode*, int);
	void insertNonFull(BNode*, pair<int, int>);
	int findIndex(int, BNode*);
	pair<bool, int> recursiveRemove(int, BNode*);
	void fill(BNode*, int);
	void merge(BNode*, int);
	int removeFromLeaf(BNode*, int);
	int removeFromNonLeaf(BNode*, int);
	pair<int, int> getPredecessor(BNode*, int);
	pair<int, int> getSuccessor(BNode*, int);

public:
	BTree(int);
	~BTree();
	pair<bool, int> search(int);
	bool insert(int, int);
	pair<bool, int> remove(int key);
};

BNode::BNode(int t, bool leaf)
{
	this->t = t;
	this->leaf = leaf;
	keys = new pair<int, int>[2 * t - 1];
	children = new BNode * [2 * t];
	size = 0;
}

BNode::~BNode()
{
	delete[] keys;
	delete[] children;
}

BTree::BTree(int t_)
{
	t = t_;
	root = nullptr;
}

// Deletes value by key
// Return pair: bool pair.first - if value was deleted 
//              int pair.second - deleted value
pair<bool, int> BTree::remove(int key)
{
	if (!root)
		return make_pair(false, -1);

	return recursiveRemove(key, root);
}

pair<bool, int> BTree::recursiveRemove(int key, BNode* node)
{
	int index = findIndex(key, root);
	int removedValue;

	if (index < node->size && node->keys[index].first == key)
	{
		if (node->leaf)
			removedValue = removeFromLeaf(node, index);
		else
			removedValue = removeFromNonLeaf(node, index);

		return make_pair(true, removedValue);
	}
	else
	{
		if (node->leaf)
			return make_pair(false, -1);

		if (node->children[index]->size < t)
			fill(node, index);

		if (index == node->size)
			recursiveRemove(key, node->children[index - 1]);
		else
			recursiveRemove(key, node->children[index]);
	}
}

// Removes value from leaf
int BTree::removeFromLeaf(BNode* node, int index)
{
	int value = node->keys[index].second;

	for (int i = index + 1; i < node->size; i++)
		node->keys[i - 1] = node->keys[i];

	node->size--;

	return value;
}

// Removes value from non-leaf
int BTree::removeFromNonLeaf(BNode* node, int index)
{
	int key = node->keys[index].first;
	int value = node->keys[index].second;

	if (node->children[index]->size >= t)
	{
		pair<int, int> pred = getPredecessor(node, index);
		node->keys[index] = pred;
		recursiveRemove(pred.first, node->children[index]);
	}
	else if (node->children[index + 1]->size >= t)
	{
		pair<int, int> succ = getSuccessor(node, index);
		node->keys[index] = succ;
		recursiveRemove(succ.first, node->children[index + 1]);
	}
	else
	{
		merge(node, index);
		recursiveRemove(key, node->children[index]);
	}

	return value;
}

// Gets the predecessor of the key
pair<int, int> BTree::getPredecessor(BNode* node, int index)
{
	BNode* current = node->children[index];

	while (!current->leaf)
		current = current->children[current->size];

	return current->keys[current->size - 1];
}

// Gets the successor of the key
pair<int, int> BTree::getSuccessor(BNode* node, int index)
{
	BNode* current = node->children[index + 1];

	while (!current->leaf)
		current = current->children[0];

	return current->keys[0];
}

// Fills node that has less than t - 1 keys
void BTree::fill(BNode* parent, int index)
{
	BNode* child = parent->children[index];

	if (index != 0 && parent->children[index - 1]->size >= t)
	{
		BNode* leftChild = parent->children[index - 1];

		for (int i = child->size - 1; i >= 0; i--)
			child->keys[i + 1] = child->keys[i];

		if (!child->leaf)
			for (int i = child->size; i >= 0; i--)
				child->children[i + 1] = child->children[i];

		child->keys[0] = parent->keys[index - 1];

		if (!child->leaf)
			child->children[0] = leftChild->children[leftChild->size];

		parent->keys[index - 1] = leftChild->keys[leftChild->size - 1];

		child->size++;
		leftChild->size--;
	}
	else if (index != parent->size && parent->children[index + 1]->size >= t)
	{
		BNode* rightChild = parent->children[index + 1];

		child->keys[child->size] = rightChild->keys[index];

		if (!child->leaf)
			child->children[child->size + 1] = rightChild->children[0];

		parent->keys[index] = rightChild->keys[0];

		for (int i = 1; i < rightChild->size; i++)
			rightChild->keys[i - 1] = rightChild->keys[i];

		if (!rightChild->leaf)
			for (int i = 1; i < rightChild->size + 1; i++)
				rightChild->children[i - 1] = rightChild->children[i];

		child->size++;
		rightChild->size--;
	}
	else
	{
		if (index != parent->size)
			merge(parent, index);
		else
			merge(parent, index - 1);
	}
}

// Merges children[index] with children[index + 1]
void BTree::merge(BNode* parent, int index)
{
	BNode* leftChild = parent->children[index];
	BNode* rightChild = parent->children[index + 1];

	leftChild->keys[t - 1] = parent->keys[index];

	for (int i = 0; i < rightChild->size; i++)
		leftChild->keys[t + i] = rightChild->keys[i];

	if (!leftChild->leaf)
		for (int i = 0; i < rightChild->size + 1; i++)
			parent->children[t + i] = rightChild->children[i];

	for (int i = index + 1; i < parent->size; i++)
		parent->keys[i - 1] = parent->keys[i];

	for (int i = index + 2; i < parent->size + 1; i++)
		parent->children[i - 1] = parent->children[i];

	leftChild->size += rightChild->size + 1;
	parent->size--;

	delete(rightChild);
}

int BTree::findIndex(int key, BNode* node)
{
	int index = 0;

	while (index < node->size && node->keys[index].first < key)
		index++;

	return index;
}

// Splits the nodes that are too full
void BTree::splitChild(BNode* x, int index)
{
	BNode* toSplit = x->children[index];
	BNode* newNode = new BNode(toSplit->t, toSplit->leaf);
	newNode->leaf = toSplit->leaf;
	newNode->size = t - 1;

	for (unsigned i = 0; i < t - 1; i++)
		newNode->keys[i] = toSplit->keys[i + t];

	if (!toSplit->leaf)
		for (unsigned j = 0; j < t; j++)
			newNode->children[j] = toSplit->children[j + t];


	toSplit->size = t - 1;

	nodeInsert(x, toSplit->keys[t - 1]);
	x->children[index + 1] = newNode;
}

// Inserts value into tree
bool BTree::insert(int key, int value)
{
	if (!root)
	{
		root = new BNode(t, true);
		root->keys[0] = make_pair(key, value);
		root->size = 1;
		return true;
	}

	if (search(key).first)
		return false;

	if (root->size == 2 * t - 1)
	{
		BNode* newRoot = new BNode(t, false);
		newRoot->children[0] = root;
		splitChild(newRoot, 0);

		int i = (newRoot->keys[0].first < key) ? 1 : 0;

		insertNonFull(newRoot->children[i], make_pair(key, value));
		root = newRoot;
	}
	else
	{
		insertNonFull(root, make_pair(key, value));
	}

	return true;
}

void BTree::nodeInsert(BNode* x, pair<int, int> key)
{
	int i;

	for (i = x->size; i > 0 && key.first < x->keys[i - 1].first; i--)
	{
		x->keys[i] = x->keys[i - 1];
		x->children[i + 1] = x->children[i];
	}

	x->children[i + 1] = x->children[i];
	x->keys[i] = key;
	x->size++;
}

// Inserts value into non-full node 
void BTree::insertNonFull(BNode* node, pair<int, int> key)
{
	int i = node->size - 1;

	if (node->leaf)
	{
		while (i >= 0 && node->keys[i].first > key.first)
		{
			node->keys[i + 1] = node->keys[i];
			i--;
		}

		node->keys[i + 1] = key;
		node->size++;
	}
	else
	{
		while (i >= 0 && node->keys[i].first > key.first)
			i--;
		i++;

		if (node->children[i]->size == 2 * t - 1)
		{
			splitChild(node, i);

			if (node->keys[i].first < key.first)
				i++;
		}

		insertNonFull(node->children[i], key);
	}
}

// Finds value by key
pair<bool, int> BTree::search(int key)
{
	if (!root)
		return make_pair(false, -1);
	else
		return recursiveSearch(key, root);
}

pair<bool, int> BTree::recursiveSearch(int key, BNode* node)
{
	// the first key greater than or equal to key
	int index = 0;
	while (index < node->size && key > node->keys[index].first)
		index++;

	if (index < node->size && node->keys[index].first == key)
		return make_pair(true, node->keys[index].second);

	if (node->leaf)
		return make_pair(false, -1);

	// go to the found child
	return recursiveSearch(key, node->children[index]);
}

BTree::~BTree()
{
	delete root;
}

void process(int t, string testPath, string outputPath)
{
	BTree tree(t);

	fstream in(testPath, ios::in);
	ofstream out(outputPath, ios::out);

	if (in.is_open() && out.is_open())
	{
		string cmd;
		int key;
		int value;

		while (in >> cmd >> key)
		{
			if (cmd == "insert")
			{
				in >> value;

				if (tree.insert(key, value))
					out << "true" << endl;
				else
					out << "false" << endl;
			}
			else if (cmd == "delete")
			{
				pair<bool, int> removeResult = tree.remove(key);

				if (removeResult.first)
					out << removeResult.second << endl;
				else
					out << "null" << endl;
			}
			else if (cmd == "find")
			{
				pair<bool, int> searchResult = tree.search(key);

				if (searchResult.first)
					out << searchResult.second << endl;
				else
					out << "null" << endl;
			}
		}

		in.close();
		out.close();
	}
}

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cout << "Wrong number of args";
		return -1;
	}

    process(atoi(argv[1]), argv[2], argv[3]);
}