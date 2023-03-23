#include "MinHeap.h"
#include <bits/stdc++.h>

class CodeNode
{
public:
    Node* node;
    string code;
    CodeNode(Node* n, string c)
    {
        this->node = n;
        this->code = c;
    }
};

void inOrderTraversal(Node* n)
{
    if (n->left != NULL)
        inOrderTraversal(n->left);

    cout << n->symbol << " : " << n->frequency << '\n';

    if (n->right != NULL)
        inOrderTraversal(n->right);
}

int main()
{
    MinHeap *mh = new MinHeap();
    int netFrequency = 0;       // Total frequency of all symbols.
    int symbolsCount = 0;       // Total count of Different symbols found.
    int symbolFrequency[257] = {0};   // Individual symbol frequency (index represents ASCII value

    ofstream outFile("text.txt");

    cout << "Enter ** to terminate.\n";
    cout << "\nEnter The Text: \n\n";

    while(true)
    {
        string s;
        getline(cin,s); // Text to be encoded.
        outFile << s << '\n';

        int length = s.length();
        netFrequency += length;     // Sum is incremented for all the new symbol entries

        for (int i=0; i<length; i++)
        {
            symbolFrequency[ (int)s[i] ]++; // Incrementing the count every time a symbol is scanned

            if ( symbolFrequency[ (int)s[i] ] == 1 )
                symbolsCount++;     // If new symbol is found, increment symbol count
        }

        if( s.find("**") != string::npos )
        {
            netFrequency -= 2;
            symbolFrequency[42] -= 2; // ASCII value of * is 42

            if (symbolFrequency[42] == 0)
                symbolsCount--;

            break;
        }
    }

    int counter = 0; // Counter for number of symbols occurred

    for (int i=0; i<257; i++)
    {
        if (symbolFrequency[i] == 0) // 0 frequency meaning no occurrence
            continue;

        // Inserting the character and its frequency as a node.
        mh->insertNode( new Node( char(i), symbolFrequency[i] ) );
        counter++;  // Incrementing for occurrence of a symbol

        if ( counter == symbolsCount ) // if all symbols occurred, exit the loop
            break;
    }

    if (mh->getSize() == 0) // No symbol condition.
    {
        cout << "\nNo Symbols Found";
        getchar();
        return 0;
    }

    if (mh->getSize() == 1)  // Single Symbol condition
    {
        Node* node = mh->extractNode();
        cout << '\n' << node->symbol << " : " << "0" << '\n';
        getchar();
        return 0;
    }

    Node* BSTroot = NULL; // The BST which will contain the code tree at the end.

    while(true) // more than 1 symbols found
    {
        // Extracting the two nodes with minimum frequencies from minHeap
        Node* node1 = mh->extractNode();
        Node* node2 = mh->extractNode();

        int f1 = node1->frequency;
        int f2 = node2->frequency;

        // new node to create a tree for node1 and node2.
        // node frequency will be sum of f1 and f2.

        BSTroot = new Node(char(512), f1+f2); // Character 512 will represent all the internal nodes

        if (f1 < f2) // the greater of the two will be right child
        {
            BSTroot->left = node1;
            BSTroot->right = node2;
        }
        else
        {
            BSTroot->left = node2;
            BSTroot->right = node1;
        }

        // Inserting the newly formed tree's root node in the heap
        mh->insertNode(BSTroot);

        // If final tree is constructed, its frequency is equal to net sum of all symbol's frequency.

        if(BSTroot->frequency == netFrequency && mh->getSize() == 1)
            break;
    }

    string CODE = "";   // string for storing the code-word of a symbol.
    queue<CodeNode*> q;
    CodeNode* Symbols_Codes[symbolsCount];int index = 0;

    q.push( new CodeNode(BSTroot, CODE) );

    while( !q.empty() )  // Level-order traversal through all nodes.
    {
        CodeNode* code_node = q.front();
        q.pop();

        if (code_node->node->left != NULL)
        {
            // Going left means a 0 in code-word
            Node* node = code_node->node;
            CODE = code_node->code + "0";
            q.push(new CodeNode(node->left, CODE) ); // Pushing the next left child-node in queue
        }

        if (code_node->node->right != NULL)
        {
            // Going right means a 1 in code-word
            Node* node = code_node->node;
            CODE = code_node->code + "1";
            q.push(new CodeNode(node->right, CODE) ); // Pushing the next right child-node in queue
        }

        // Leaf Node Condition - Leaf node is the node containing a symbol
        if (code_node->node->left == NULL && code_node->node->right == NULL)
            Symbols_Codes[index++] = code_node;


    }

    system("CLS");
    cout << "CODE - WORDS: \n\n";
    for (int i=0; i<index; i++)
    {
        // Symbol and code-word printing
        char Symbol = Symbols_Codes[i]->node->symbol;
        string code = Symbols_Codes[i]->code;

        printf("\n  \'%c\' : ", Symbol); cout << code << '\n';
        outFile << "\n  \'" << Symbol << "\' = " << code << '\n';
    }
    getchar();


    outFile.close();
    ifstream inFile("text.txt");
    outFile.open("Coded.txt");

    system("CLS");
    cout << "ENCODED TEXT: \n\n";

    while( inFile.eof() == 0 ) // while End-Of-File doesn't occur, run the loop
    {
        string str;
        getline(inFile, str);   // Reading the input text stored in a file
        int length = str.length();

        for (int i=0; i<length; i++)
        {
            char ch = str[i]; // reading each symbol
            string code = "";

            if (i < length - 1)
                if (str[i] == '*' && str[i+1] == '*') // Exit condition
                    goto DECODING;

            for (int j=0; j<index; j++) // Running through all symbol
            {
                if (Symbols_Codes[j]->node->symbol == ch)
                {
                    code = Symbols_Codes[j]->code;  // Exiting with code-word required
                    break;
                }
            }

            cout << code;   // printing the code-word for the corresponding symbol
            outFile << code;
        }
        outFile << '\n';
        cout << '\n';
    }

    DECODING:
        inFile.close();
        outFile.close();
    getchar();

    system("CLS");
    cout << "DECODED TEXT: \n\n";

    inFile.open("Coded.txt");

    while ( inFile.eof() == 0 ) // while End-Of-File doesn't occur, continue the loop
    {
        string str;
        getline(inFile, str); // reading line from the coded file

        int length = str.length();

        Node* current = BSTroot;

        for(int i=0; i<length; i++) // Traversal through the BST containing the symbols
        {
            if ( str[i] == '0' )    // left sub-tree is indicated by 0
                current = current->left;
            else                    // right sub-tree is indicated by 1
                current = current->right;

            if (current->left == NULL && current->right == NULL)
            {
                // leaf node indicates a text symbol
                cout << current->symbol;
                current = BSTroot;

                // Again traversing from the root;
            }
        }
        cout << '\n';
    }

    getchar();
    return 0;
}
