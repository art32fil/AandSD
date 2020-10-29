namespace list {

    typedef int base;
    class Stack {
    private:
        struct node;
        node *topOfStack;
    public:
        Stack (){
            topOfStack = nullptr;
        };
        base pop();
        void push (const base &x);
        void destroy ();
    };
}