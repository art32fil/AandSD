#include "RedBlackTree.h"

using namespace std;


int main()
{
    setlocale( 0, "ru-RU");
    bool flag = true;
    int options; 
    bool hesTree = false;
    Node *root;
    int elem;
    string name;
    ofstream output;
    while (flag)
    {
        cout << "\nвыберите один из вариантов:\n";
        cout << "[1] Добавить элемент:\n";
        cout << "[2] Добавить элементы из файла:\n";
        cout << "[3] Добавить элементы из консоли:\n";
        cout << "[4] Удалить элемент:\n";
        cout << "[5] Показать дерево:\n";
        cout << "[6] записать в файл по возрастанию:\n";
        cout << "[7] подсчитать количество вхождений:\n";
        cout << "[8] Выход:\n";
        cout << ">>> ";
        cin >> options;
        switch (options)
        {
        case 1:
            cout << "Пожалуйста, напишите элемент (целые числа): ";
            cin >> elem;
            root = Insert(root, new Node(elem, RED));
            break;
        case 2:
            root = ReadFromFile( root );
            break;
        case 3:
            root = ReadFromConsole( root );
            break;
        case 4:
            cout << "Пожалуйста, напишите элемент (целые числа): ";
            cin >> elem;
            deleteElem( root, elem );
            break;
        case 5:
            showForestOnConcole(root, 0);
            // ShowForestWithoutColor(root, 0 );
            break;
        case 6:
            cout << "пожалуйста, напишите имя файла: ";
            cin >> name;
            output.open( name , ios_base::out );
            WriteToFile( root, output);
            output.close();
            break;        
        case 7:
            cout << "Пожалуйста, напишите элемент (целые числа): ";
            cin >> elem;
            cout << "элемент существует "<< CountElem( root, elem )<<" раз\n";
            break;        
        case 8:
            cout << "пока!!\n";
            flag = false;
            break;        
        default:

            break;
        }

    }
	return 0;
}



int CountElem(Node *elem, int key){

    int l = 0, r = 0; 
    if(elem->Left())
        l = CountElem(elem->Left(), key);

    if(elem->Right())
        r = CountElem(elem->Right(), key);  

    if( elem->getVal() == key ){
        return 1+l+r;
    }
    return l+r;
}

Node* ReadFromFile( Node* head ){

    string name;
    cout << "пожалуйста, напишите имя файла: ";
    cin >> name;
    ifstream input( name );
    int len;
    input >> len;
    int *OutArray = new int[len];
    cout << ">>> Arr["<< len <<"]:\n{ ";
    for (int i = 0; i < len; i++)
    {
        input >> OutArray[i];
        cout << OutArray[i] <<" ";
    }
    cout << "}\n";
    createForest(head, OutArray , len );
    delete [] OutArray;
    return head;
}

Node* ReadFromConsole(Node *head){

    int len;
    cout << "пожалуйста, напишите количество элементов:\n>>> ";
    cin >> len;
    cout << "пожалуйста, пишите элементы через пробел:\n>>> ";
    int *OutArray = new int[len];
    for (int i = 0; i < len; i++)
    {
        cin >> OutArray[i];
    }
    cout << "\n";
    createForest(head, OutArray , len );
    delete [] OutArray;
    return head;
}



void WriteToFile(Node *elem, ofstream &fout)
{
    if( elem->Left() ){

	    WriteToFile(elem->Left(), fout);
    }
	fout << elem->getVal() <<", ";	
    if( elem->Right() ){

	    WriteToFile(elem->Right(), fout);
    }
}


bool isLeaf(Node *elem){
	return elem == nullptr;
}

bool isNotLeaf(Node *elem){
	return elem != nullptr;
}

Node * Root(Node* elem){

	Node *root = elem;
    if(root){
        while (root->Parent())
        {
            root = root->Parent();
        }
    }
	return root;
};


Node *findElem(Node *root, int key)
{
	Node *tmp = root;
	while (tmp != nullptr)
	{
		if (tmp->getVal() == key)
		{
			return tmp;
		}
		if (tmp->getVal() > key)
		{
			tmp = tmp->Left();
		}
		else
		{
			tmp = tmp->Right();
		}
	}
	return nullptr;
}

void showForestOnConcole(Node *root, int n)
{
	if( !root || root == nullptr ){

		for (int i = 0; i < n; i++)	cout << "\t";

		cout << "\x1b[40;40m    \x1b[0m \n";
		return;
	}


	showForestOnConcole(root->Left(), n + 1);
	
	for (int i = 0; i < n; i++)
	{
		cout << "\t";
	}
	cout << "\x1b[40;4" + std::to_string(root->color()) + "m " + to_string(root->getVal()) + " \x1b[0m \n";
	
	showForestOnConcole(root->Right(), n + 1);
	cout << "\n";
}


void ShowForestWithoutColor(Node *root, int n)
{
	if( !root ){
		
		for (int i = 0; i < n; i++)	
            cout << "\t";
	
		cout << "[ ]\n";
		return;
	}

	ShowForestWithoutColor(root->Left(), n + 1);
	
	for (int i = 0; i < n; i++)	
        cout << "\t";
    
    cout << root->getVal();
	
    if(root->color() == BLACK)
        cout << "[x]\n" ;
    else
        cout << "[-]\n" ;
        
	ShowForestWithoutColor(root->Right(), n + 1);
	
}



void free(Node *elem){

	if( isLeaf( elem )){

        return;
    } 
    if( isLeft ( elem ) ) {

        Parent(elem )->Left() = nullptr;
    } 
    else if( isRight ( elem )  )
    {
        Parent(elem)->Right() = nullptr;
    }		
		
	delete elem;
	elem = nullptr;
}



//! Helper functions:

bool isRed(Node *elem)
{
	if (elem != nullptr)
		return elem->color() == RED;

	return false;
}

bool isBlack(Node *elem)
{
	if (elem != nullptr){

		return elem->color() == BLACK;
	}
	
	return true;
}

bool isLeft(Node *elem)
{
	if (Parent(elem))
		return Parent(elem)->Left() == elem;

	return false;
}

bool isRight(Node *elem)
{
	if (Parent(elem))
		return Parent(elem)->Right() == elem;
	return false;
}

Node *Parent(Node *elem)
{
	// * Обратите внимание, что для корневого узла родительский элемент имеет значение null.
	return elem == nullptr ? nullptr : elem->Parent();
}

Node *GrandParent(Node *elem)
{
	// * Обратите внимание, что он вернет nullptr, если это root или дочерний элемент root
	return Parent(Parent(elem));
}

Node *Brother(Node *elem)
{
	// * Отсутствие родителя означает отсутствие брата или сестры.
	if (Parent(elem))
	{
		if (isLeft(elem))
		{
			return Parent(elem)->Right();
		}
		else
		{

			return Parent(elem)->Left();
		}
	}

	return nullptr;
}

Node *Uncle(Node *elem)
{
	//* Отсутствие родителя означает отсутствие дяди
	return Brother(Parent(elem));
}

//! start algorthim


void RotateLeft(Node *elem)
{
	Node *Son = elem->Right();
    Node *parent = Parent(elem );
	Son->Parent() = parent; //* при этом, возможно, Son становится корнем дерева

	if ( parent )
	{
		if (isLeft(elem))
		{
			parent->Left() = Son;
		}
		else
		{
			parent->Right() = Son;
		}
	}
	
    
	
	elem->Right() = Son->Left();

	if (Son->Left())
	{
		Son->Left()->Parent() = elem;
	}
	elem->Parent() = Son;
	Son->Left() = elem;    

}

void RotateRight(Node *elem)
{
	Node *Son = elem->Left();
    Node *parent = Parent(elem );
	Son->Parent() = parent; //* при этом, возможно, Son становится корнем дерева

	if (parent)
	{
		if (isLeft(elem))
		{
			parent->Left() = Son;
		}
		else
		{
			parent->Right() = Son;
		}
	}

	elem->Left() = Son->Right();

	if ( Son->Right() )
		Son->Right()->Parent() = elem;

	elem->Parent() = Son;
	Son->Right() = elem;
}

void InsertRecurse(Node *&current, Node *elem)
{
	//? Рекурсивно спускайтесь по дереву до тех пор, пока не будет найден лист.
	if (current != nullptr)
	{
		//? если текущее значение больше чем новое значение, то слева от этого
		if (current->getVal() > elem->getVal())
		{
			//? если левая сторона узла не пуста
			if (current->Left() != nullptr)
			{
				//* Рекурсивно спускаться влево-вниз
				InsertRecurse(current->Left(), elem);
				return;
			}
			
			//? если левая сторона узла пуста
			//* присваивать значение на левом узле
			current->Left() = elem;

		}
		else //? если текущее значение меньше чем новое значение, то справа от этого
		{
			//? если правая сторона узла не пуста
			if (current->Right() != nullptr)
			{
				//* Рекурсивно спускаться право-вниз
				InsertRecurse(current->Right(), elem);
				return;
			}
			
			//? если правая сторона узла пуста
			//* присваивать значение на правом узле
			current->Right() = elem;
			
		}
	}
	//* сделать текущий элемент родительским для нового элемента
	elem->Parent() = current;
}

void fixProperties(Node *elem)
{

	if (!Parent(elem))
	{

		elem->color() = BLACK;
		return;
	}
	else if (isBlack(Parent(elem)))
	{
		return;
	}
	else if (Uncle(elem) != nullptr && isRed(Uncle(elem)))
	{
		Parent(elem)->color() = BLACK;
		Uncle(elem)->color() = BLACK;
		GrandParent(elem)->color() = RED;
		fixProperties(GrandParent(elem));
		return;
	}
	else if (isRight(elem) && isLeft(Parent(elem)))
	{
		RotateLeft(Parent(elem));
		elem = elem->Left();
	}
	else if (isLeft(elem) && isRight(Parent(elem)))
	{
		RotateRight(Parent(elem));
		elem = elem->Right();
	}

	Parent(elem)->color() = BLACK;
	GrandParent(elem)->color() = RED;

	if (isLeft(elem) && isLeft(Parent(elem)))
	{
		RotateRight(GrandParent(elem));
	}
	else
	{

		RotateLeft(GrandParent(elem));
	}
}

Node *Insert(Node *root, Node *elem)
{
	//* Вставить новый узел в текущее дерево.
	InsertRecurse(root, elem);

	//* Восстановите дерево в случае нарушения какого-либо из красно-черных свойств.
	fixProperties(elem);
	//* Найти новый корень для возврата.
	root = elem;
	while (root->Parent())
	{
		root = root->Parent();
	}
	return root;
}

//* создание леса из массива значений
void createForest(Node *&root, int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		root = Insert(root, new Node(arr[i], RED));
	}
}


void deleteElem(Node*& root, int key)
{
    if(!root) {
        cout << "пустое дерево!!!\n";
        return;
    }

    Node *elem = findElem( root, key);
    if(!elem) {
        cout << "этот "<< key <<" элемент не существует в структуре!!!\n";
        return;
    }

    if( !Parent( elem )){    
        
        if( elem->Left() && !elem->Right()){
            if(!elem->Left()->Left() || !elem->Left()->Right()){
                
                root = elem->Left();
                root->Parent() = nullptr; 
                root->color() = BLACK;
                free( elem );
                return;
            }
        }
        else if( elem->Right() && !elem->Left() )
        {
            if(!elem->Right()->Left() && !elem->Right()->Right()){

                root = elem->Right();
                root->Parent() = nullptr; 
                root->color() = BLACK;
                free( elem );
                return;
            }
        }
        else if( !elem->Left() && !elem->Right() )
        {
            free( elem );
            root = nullptr;
            return;
        }    
    }
    deleteNode(elem);
    
    root = Root(root);
}



void deleteFixup(Node *elem) {

	Node *root = Root( elem );

    while (elem != root && isBlack( elem )) {
        if ( isLeft( elem ) ) {
            Node *w = Parent( elem )->Right();
            if (w->color() == RED) {

                w->color() = BLACK;
                Parent( elem )->color() = RED;
                RotateLeft( Parent( elem ) );
                w = Parent( elem )->Right();

            }
            if ((isLeaf( w->Left()) || isBlack( w->Left() ))&&( isLeaf( w->Right()) || isBlack( w->Right() ))) {
                
                w->color() = RED;
                elem = Parent(elem);
            } 
            else {
                if (isBlack( w->Right() )) {
                    w->Left()->color() = BLACK;
                    w->color() = RED;
                    RotateRight ( w );
                    w = Parent( elem )->Right();
                }
                w->color() = Parent( elem )->color();
                Parent( elem )->color() = BLACK;
                w->Right()->color() = BLACK;
                RotateLeft ( Parent( elem ) );
                elem = root;
            }
        } else {
            Node *w = Parent( elem )->Left();
            if (w->color() == RED) {

                w->color() = BLACK;
                Parent( elem )->color() = RED;
                RotateRight ( Parent( elem ) );
                w = Parent( elem )->Left();
            }
            if ( (isLeaf(w->Right()) || isBlack( w->Right())) && 
			 	(isLeaf( w->Left() ) || isBlack( w->Left()))){
                w->color() = RED;
                elem = Parent( elem );
            } else {
                if ( isBlack( w->Left() )) {
                    w->Right()->color() = BLACK;
                    w->color() = RED;
                    RotateLeft( w );
                    w = Parent( elem )->Left();
                }
                w->color() = Parent( elem )->color();
                Parent( elem )->color() = BLACK;
                w->Left()->color() = BLACK;
                RotateRight ( Parent( elem ) );
                elem = root;
            }
        }
    }
    elem->color() = BLACK;
}


void deleteNode(Node *elem) {

       Node *x, *descendant;

    if (!elem){
        return;
    } 
	Node *root = Root(elem);

    if (isLeaf(elem->Left()) || isLeaf( elem->Right() )) {

        descendant = elem;
    } else {

        descendant = elem->Right();
        while (descendant->Left()){

            descendant = descendant->Left();
        } 
    }
	if ( descendant->Left() || descendant->Right() ) {
		if (descendant->Right() ){
			x = descendant->Right();
        }
		else {
    		x = descendant->Left();
        }
    	x->Parent() = descendant->Parent();

		if (Parent( descendant ))
        {
            if ( isLeft( descendant ) )
            {
                Parent( descendant )->Left() = x;
            }
            else {

                Parent(descendant)->Right() = x;
            }
        }
		if (descendant != elem) {

        	elem->setValue( descendant->getVal() );        
        }
		
        if (isBlack( descendant ))
        {
            deleteFixup (x);
        }	
	}
	else
	{
		if (descendant != elem) 
			elem->setValue( descendant->getVal() );

		if (isBlack( descendant ))
			deleteFixup (descendant);

	}
	free(descendant);
}

