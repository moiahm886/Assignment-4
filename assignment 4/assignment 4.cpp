#include<iostream>
#include<string>
using namespace std;
struct Node
{
	string name;
	float CGPA;
	string program, department, Reg_NO;
	Node* left;
	Node* right;
};
class Student
{
	string name;
	float CGPA;
	string program, department, Reg_NO;
public:
	Student()
	{
		name = '\0';
		program = '\0';
		department = '\0';
		Reg_NO = '\0';
		CGPA = 0.0;
	}
	~Student() {};
	void setname(string name)
	{
		this->name = name;
	}
	void setCGPA(float CGPA)
	{
		this->CGPA = CGPA;
	}
	void setprogram(string program)
	{
		this->program = program;
	}
	void setdepartment(string department)
	{
		this->department = department;
	}
	void setReg_No(string Reg_NO)
	{
		this->Reg_NO = Reg_NO;
	}
	string getname()
	{
		return name;
	}
	string getdepartment()
	{
		return department;
	}
	string getprogram()
	{
		return program;
	}
	string getReg_NO()
	{
		return Reg_NO;
	}
	float getCGPA()
	{
		return CGPA;
	}
};
Node* newnode(Node* root, Student S)
{
	Node* NewNode = new Node();
	NewNode->name = S.getname();
	NewNode->CGPA = S.getCGPA();
	NewNode->program = S.getprogram();
	NewNode->department = S.getdepartment();
	NewNode->Reg_NO = S.getReg_NO();
	NewNode->right = NULL;
	NewNode->left = NULL;
	return NewNode;
}
Node* insertion(Node* root, Student S)
{
	if (root == NULL)
	{
		return newnode(root, S);
	}
	else
	{
		if (S.getReg_NO()>root->Reg_NO)
		{
			root->right = insertion(root->right, S);
		}
		else if (S.getReg_NO() < root->Reg_NO)
		{
			root->left = insertion(root->left, S);
		}
		else
		{
			cout << "Cannot have same registration number\n";
		}
	}
	return root;
}
Node* minimumvalue(Node* root)
{
	struct Node* current = root;
	while (current && current->left != NULL)
	{
		current = root->left;
	}
	return current;
}
struct Node* deletion(struct Node* root, string key)
{
	if (root == NULL)
	{
		return root;
	}
	if (root->Reg_NO > key) // if registration number is lesser than roots registration number it will travese to the left side of tree
	{
		root->left=deletion(root->left, key);
	}
	else if (root->Reg_NO < key)
	{
		root->right=deletion(root->right, key);
	}
	else
	{
		if (root->right == NULL)
		{
			struct Node* temp = root->left;
			free(root);
			return temp;
		}
		else if (root->left == NULL)
		{
			struct Node* temp = root->right;
			free(root);
			return temp;
		}
		struct Node* temp = minimumvalue(root->right); //if both childs exist it will swap the root with the minimum value of the higher side.
		root->Reg_NO = temp->Reg_NO;
		root->right = deletion(root->right, temp->Reg_NO);
	}
	return root;

}
int height(Node* root)
{
	int h;
	int Lcount = 0;
	int Rcount = 0;
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		int Lcount = height(root->left);
		int Rcount = height(root->right);
		int maxheight = max(Lcount, Rcount);
		h = maxheight + 1;
	}
	return h;

}
void display(Node* root)// inorder display
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		display(root->left);
		cout << "Student Name is " << root->name << endl;
		cout << "Student Registration Number is " << root->Reg_NO << endl;
		cout << "Student Program is " << root->program << endl;
		cout << "Student Department is " << root->department << endl;
		cout << "Student CGPA is " << root->CGPA << endl;
		cout << endl;
		display(root->right);
	}
}

int main()
{
	Node* root = NULL;
	Student S;
	string name;
	float CGPA;
	string program, department, Reg_NO;
	char ch{};
	do
	{
		jump:
		cout << "Press [I] to insert the student detail\n";
		cout << "Press [H] to know the height of the tree\n";
		cout << "Press [S] to display all the students detail\n";
		cout << "Press [D] to delete the student \n";
		cout << "Enter your choice\n";
		cin >> ch;
		ch = tolower(ch);
		switch (ch)
		{
		case 'i':
			cout << "Enter Name of the student\n";
			cin.ignore();
			getline(cin, name);
			cout << "Enter Registration number of the student\n";
			cin.ignore();
			getline(cin, Reg_NO);
			cout << "Enter Program of the student\n";
			cin.ignore();
			getline(cin, program);
			cout << "Enter Department of the student\n";
			cin.ignore();
			getline(cin, department);
			cout << "Enter CGPA of the student\n";
			cin >> CGPA;
			S.setname(name);
			S.setdepartment(department);
			S.setCGPA(CGPA);
			S.setprogram(program);
			S.setReg_No(Reg_NO);
			root = insertion(root, S);
			break;
		case 'h':
			cout << "The height of the tree is" << height(root) << endl;;
			break;
		case 's':
			display(root);
			break;
		case 'd':
			cout << "Enter Registration Number you want to delete\n";
			cin.ignore();
			getline(cin, Reg_NO);
			deletion(root, Reg_NO);
			break;
		default:
			goto jump;
			break;
		}
		cout << "Do you want to continue Y/N\n";
		cin >> ch;
		ch = tolower(ch);
	} while (ch == 'y');
	system("pause");
	return 0;
}