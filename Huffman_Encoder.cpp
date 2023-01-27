/*
Gabe Sibulkin, Huffman Encoder, Submitted 12/12/22
*/

#include <iostream>
#include <queue>
#include <map>
#include <string>
using namespace std;

map<char, string> codes;

map<char, int> freq;

//huffman tree nodes
struct node
{
	char data;
	int freq;
	node* left, * right;

	node(char data, int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

struct compare // compare nodes
{
	bool operator()(node* l, node* r)
	{
		return (l->freq > r->freq);
	}
};

void storeCodes(struct node* root, string str) // places ones and zeros
{
	if (root == NULL)
	{
		return;
	}

	if (root->data != '/0')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

priority_queue<node*, vector<node*>, compare> Heap; //Define the heap priority queue

void huffcode(int size) //builds tree
{
	struct node* left, * right, * top;

	for (map<char, int>::iterator iter = freq.begin(); iter != freq.end(); iter++)
	{
		Heap.push(new node(iter->first, iter->second));
	}

	while (Heap.size() != 1)
	{
		left = Heap.top();

		Heap.pop();

		right = Heap.top();

		Heap.pop();

		top = new node('/0', left->freq + right->freq);

		top->left = left;

		top->right = right;

		Heap.push(top);
	}

	storeCodes(Heap.top(), "");
}

void Freq(string str, int n) // calculates letter frequency
{
	for (int i = 0; i < str.size(); i++)
	{
		freq[str[i]]++;
	}

}

string decode(struct node* root, string s) // produces decoded string by iteration
{
	string ans = "";

	struct node* pos = root;

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '0')
		{
			pos = pos->left;
		}

		else
		{
			pos = pos->right;
		}

		if (pos->left == NULL && pos->right == NULL)
		{
			ans += pos->data;
			pos = root;
		}
	}
	return ans + '\0';
}

string strtobin(string s) // conversion of string to binary
{
	int len = s.length();

	string binstr;


	for (int i = 0; i <= len; i++)
	{

		int val = int(s[i]);


		string bin = "";

		while (val > 0)
		{
			(val % 2) ?

				bin.push_back('1') :

				bin.push_back('0');

			val /= 2;
		}
		reverse(bin.begin(), bin.end());

		binstr += bin;

	}

	return binstr;
}

void percentsavings(string rawbin, string encstr) // calculates the percent savings of encoding, saw this and thought I'd add 
{
	double rawlength, enclength, diff, percent = 0;

	rawlength = rawbin.length();
	enclength = encstr.length();

	diff = rawlength - enclength;
	percent = diff / enclength;
	percent = percent * 100;

	cout << percent << "%";
}


int main() // Driver code
{
	string str, encstr, decstr, rawbin;

	cout << "Enter in String to be Encoded: ";

	getline(cin, str);

	cout << "String Entered: " << str << endl;

	cout << "Raw string bit values: " << endl;

	rawbin = strtobin(str);

	cout << rawbin;

	Freq(str, str.length());

	huffcode(str.length());

	cout << endl << "Character With there Frequencies: " << endl;

	for (auto iter = codes.begin(); iter != codes.end(); iter++)
	{
		cout << iter->first << ' ' << iter->second << endl;
	}


	for (auto index : str)
	{
		encstr += codes[index];
	}

	cout << "\nEncoded Huffman data: " << endl << encstr << endl;

	decstr = decode(Heap.top(), encstr);

	cout << "\nDecoded Huffman Data: " << endl << decstr << endl;

	cout << "Percent Savings with Encoding: " << endl;

	percentsavings(rawbin, encstr);

	return 0;
}




